/******************************************************************
 *
 * Foreman for C++
 *
 * Copyright (C) 2017 Satoshi Konno. All rights reserved.
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#include <foreman/Const.h>
#include <foreman/common/Errors.h>
#include <foreman/registry/impl/SQLStore.h>
#include <foreman/util/UUID.h>

using namespace Foreman::Registry;

#define FOREMANCC_REGISTRY_SQLITESTORE_REGISTRY_TABLE "registry"
#define FOREMANCC_REGISTRY_SQLITESTORE_REGISTRY_TABLE_DDL "create table if not exists registry (id text, name text, pid text, data text, prop text, primary key(id))"
#define FOREMANCC_REGISTRY_SQLITESTORE_REGISTRY_CREATE "insert into registry (id, pid, name, data, prop) values (?, ?, ?, ?, ?)"
#define FOREMANCC_REGISTRY_SQLITESTORE_REGISTRY_UPDATE "update registry set name = ?, data = ?, prop = ? where id = ?"
#define FOREMANCC_REGISTRY_SQLITESTORE_REGISTRY_DELETE "delete from registry where id = ?"
#define FOREMANCC_REGISTRY_SQLITESTORE_REGISTRY_SELECT_BY_ID "select pid, name, data, prop from registry where id = ?"
#define FOREMANCC_REGISTRY_SQLITESTORE_REGISTRY_SELECT_BY_PARENTID "select id, name, data, prop from registry where pid = ?"
#define FOREMANCC_REGISTRY_SQLITESTORE_REGISTRY_TRUNCATE "delete from registry"

////////////////////////////////////////////////
// SQLiteStore
////////////////////////////////////////////////

SQLiteStore::SQLiteStore()
{
  db_ = NULL;
}

SQLiteStore::~SQLiteStore()
{
}

////////////////////////////////////////////////
// getLastDetailError
////////////////////////////////////////////////

bool SQLiteStore::getLastDetailError(Error* err)
{
  if (!db_)
    return false;

  err->setDetailCode(sqlite3_errcode(db_));
  err->setDetailMessage(sqlite3_errmsg(db_));

  return true;
}

////////////////////////////////////////////////
// getType
////////////////////////////////////////////////

const char* SQLiteStore::getType()
{
  return "SQLite";
}

////////////////////////////////////////////////
// open
////////////////////////////////////////////////

bool SQLiteStore::open()
{
  if (sqlite3_open(":memory:", &db_) != SQLITE_OK)
    return false;

  if (!query(FOREMANCC_REGISTRY_SQLITESTORE_REGISTRY_TABLE_DDL))
    return false;

  return true;
}

////////////////////////////////////////////////
// isOpened
////////////////////////////////////////////////

bool SQLiteStore::isOpened()
{
  if (!db_)
    return false;

  return true;
}

////////////////////////////////////////////////
// close
////////////////////////////////////////////////

bool SQLiteStore::close()
{
  if (!db_)
    return false;

  if (sqlite3_close(db_) != SQLITE_OK)
    return false;

  return true;
}

////////////////////////////////////////////////
// clear
////////////////////////////////////////////////

bool SQLiteStore::clear()
{
  if (!query(FOREMANCC_REGISTRY_SQLITESTORE_REGISTRY_TRUNCATE))
    return false;

  return true;
}

////////////////////////////////////////////////
// query
////////////////////////////////////////////////

bool SQLiteStore::query(const std::string& query)
{
  if (!isOpened())
    return false;

  char* errMsg = NULL;
  if (sqlite3_exec(db_, query.c_str(), NULL, NULL, &errMsg) != SQLITE_OK)
    return false;

  return true;
}

////////////////////////////////////////////////
// prepare
////////////////////////////////////////////////

bool SQLiteStore::prepare(const std::string& query, sqlite3_stmt** ppStmt)
{
  if (!isOpened())
    return false;

  if (sqlite3_prepare(db_, query.c_str(), (int)query.length(), ppStmt, NULL) != SQLITE_OK)
    return false;

  return true;
}

////////////////////////////////////////////////
// createObject
////////////////////////////////////////////////

bool SQLiteStore::createObject(Object* obj, Error* err)
{
  if (!obj->hasParentId() || !obj->hasName()) {
    FOREMANCC_ERROR_SET_ERRORNO(err, ERROR_INVALID_PARAMS);
    return false;
  }

  if (obj->hasId()) {
    if (getObject(obj->getId(), NULL, err)) {
      FOREMANCC_ERROR_SET_ERRORNO(err, ERROR_INVALID_PARAMS);
      return false;
    }
  }
  else {
    std::string uuid;
    if (!CreateUUID(uuid)) {
      FOREMANCC_ERROR_SET_ERRORNO(err, ERROR_INTERNAL_ERROR);
      return false;
    }
    obj->setId(uuid);
  }

  if (!obj->isRootParentId()) {
    Object parentObj;
    if (!getObject(obj->getParentId(), NULL, err)) {
      FOREMANCC_ERROR_SET_ERRORNO(err, ERROR_INVALID_PARAMS);
      return false;
    }
  }

  sqlite3_stmt* stmt = NULL;

  if (!prepare(FOREMANCC_REGISTRY_SQLITESTORE_REGISTRY_CREATE, &stmt)) {
    FOREMANCC_ERROR_SET_ERRORNO(err, ERROR_INTERNAL_ERROR);
    return false;
  }

  sqlite3_bind_text(stmt, 1, obj->objId.c_str(), (int)obj->objId.length(), SQLITE_STATIC);
  sqlite3_bind_text(stmt, 2, obj->parentId.c_str(), (int)obj->parentId.length(), SQLITE_STATIC);
  sqlite3_bind_text(stmt, 3, obj->name.c_str(), (int)obj->name.length(), SQLITE_STATIC);
  sqlite3_bind_text(stmt, 4, obj->data.c_str(), (int)obj->data.length(), SQLITE_STATIC);
  sqlite3_bind_text(stmt, 5, obj->propData.c_str(), (int)obj->propData.length(), SQLITE_STATIC);

  if (sqlite3_step(stmt) != SQLITE_DONE) {
    FOREMANCC_ERROR_SET_ERRORNO(err, ERROR_INVALID_PARAMS);
    sqlite3_finalize(stmt);
    return false;
  }

  sqlite3_finalize(stmt);

  return true;
}

////////////////////////////////////////////////
// updateObject
////////////////////////////////////////////////

bool SQLiteStore::updateObject(Object* obj, Error* err)
{
  if (!obj->hasId()) {
    FOREMANCC_ERROR_SET_ERRORNO(err, ERROR_INVALID_PARAMS);
    return false;
  }

  sqlite3_stmt* stmt = NULL;

  if (!prepare(FOREMANCC_REGISTRY_SQLITESTORE_REGISTRY_UPDATE, &stmt)) {
    FOREMANCC_ERROR_SET_ERRORNO(err, ERROR_INTERNAL_ERROR);
    return false;
  }

  sqlite3_bind_text(stmt, 1, obj->name.c_str(), (int)obj->name.length(), SQLITE_STATIC);
  sqlite3_bind_text(stmt, 2, obj->data.c_str(), (int)obj->data.length(), SQLITE_STATIC);
  sqlite3_bind_text(stmt, 3, obj->propData.c_str(), (int)obj->propData.length(), SQLITE_STATIC);
  sqlite3_bind_text(stmt, 4, obj->objId.c_str(), (int)obj->objId.length(), SQLITE_STATIC);

  if (sqlite3_step(stmt) != SQLITE_DONE) {
    sqlite3_finalize(stmt);
    return false;
  }

  sqlite3_finalize(stmt);

  return true;
}

////////////////////////////////////////////////
// getObject
////////////////////////////////////////////////

bool SQLiteStore::getObject(const std::string& objId, Object* obj, Error* err)
{
  if (objId.length() <= 0) {
    FOREMANCC_ERROR_SET_ERRORNO(err, ERROR_INVALID_PARAMS);
    return false;
  }

  sqlite3_stmt* stmt = NULL;

  if (!prepare(FOREMANCC_REGISTRY_SQLITESTORE_REGISTRY_SELECT_BY_ID, &stmt)) {
    FOREMANCC_ERROR_SET_ERRORNO(err, ERROR_INTERNAL_ERROR);
    return false;
  }

  sqlite3_bind_text(stmt, 1, objId.c_str(), (int)objId.length(), SQLITE_STATIC);

  if (sqlite3_step(stmt) != SQLITE_ROW) {
    sqlite3_finalize(stmt);
    return false;
  }

  if (obj) {
    obj->setId(objId);
    obj->setParentId((const char*)sqlite3_column_text(stmt, 0));
    obj->setName((const char*)sqlite3_column_text(stmt, 1));
    unsigned const char* data = sqlite3_column_text(stmt, 2);
    if (data) {
      obj->setData((const char*)data);
    }
    unsigned const char* prop = sqlite3_column_text(stmt, 3);
    if (prop) {
      obj->setPropertyData((const char*)prop);
    }
  }

  sqlite3_finalize(stmt);

  return true;
}

////////////////////////////////////////////////
// deleteObject
////////////////////////////////////////////////

bool SQLiteStore::deleteObject(const std::string& objId, Error* err)
{
  if (objId.length() <= 0) {
    FOREMANCC_ERROR_SET_ERRORNO(err, ERROR_INVALID_PARAMS);
    return false;
  }

  sqlite3_stmt* stmt = NULL;

  if (!prepare(FOREMANCC_REGISTRY_SQLITESTORE_REGISTRY_DELETE, &stmt)) {
    FOREMANCC_ERROR_SET_ERRORNO(err, ERROR_INTERNAL_ERROR);
    return false;
  }

  sqlite3_bind_text(stmt, 1, objId.c_str(), (int)objId.length(), SQLITE_STATIC);

  if (sqlite3_step(stmt) != SQLITE_DONE) {
    sqlite3_finalize(stmt);
    return false;
  }

  sqlite3_finalize(stmt);

  return true;
}

////////////////////////////////////////////////
// browse
////////////////////////////////////////////////

bool SQLiteStore::browse(Query* q, Objects* objs, Error* err)
{
  if (!q->hasParentId()) {
    FOREMANCC_ERROR_SET_ERRORNO(err, ERROR_INVALID_PARAMS);
    return false;
  }

  sqlite3_stmt* stmt = NULL;

  if (!prepare(FOREMANCC_REGISTRY_SQLITESTORE_REGISTRY_SELECT_BY_PARENTID, &stmt)) {
    FOREMANCC_ERROR_SET_ERRORNO(err, ERROR_INTERNAL_ERROR);
    getLastDetailError(err);
    return false;
  }

  sqlite3_bind_text(stmt, 1, q->parentId.c_str(), (int)q->parentId.length(), SQLITE_STATIC);

  while (sqlite3_step(stmt) == SQLITE_ROW) {
    Object* obj = new Object();
    if (!obj)
      break;

    obj->setParentId(q->getParentId());
    obj->setId((const char*)sqlite3_column_text(stmt, 0));
    obj->setName((const char*)sqlite3_column_text(stmt, 1));
    unsigned const char* data = sqlite3_column_text(stmt, 2);
    if (data) {
      obj->setData((const char*)data);
    }
    unsigned const char* prop = sqlite3_column_text(stmt, 3);
    if (prop) {
      obj->setPropertyData((const char*)prop);
    }

    objs->addObject(obj);
  }

  sqlite3_finalize(stmt);

  return true;
}

////////////////////////////////////////////////
// search
////////////////////////////////////////////////

bool SQLiteStore::search(Query* q, Objects* objs, Error* err)
{
  return false;
}
