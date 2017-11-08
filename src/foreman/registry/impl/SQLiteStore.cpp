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
#include <foreman/registry/impl/SQLStore.h>

using namespace Foreman::Registry;

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
// getVersion
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

  if (!query(FOREMANCC_REGISTRY_SQLITESOTORE_REGISTRY_TABLE_DDL))
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
  if (!query(FOREMANCC_REGISTRY_SQLITESOTORE_REGISTRY_TRUNCATE))
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
  sqlite3_stmt* stmt = NULL;

  if (!prepare(FOREMANCC_REGISTRY_SQLITESOTORE_REGISTRY_CREATE, &stmt))
    return false;

  sqlite3_bind_text(stmt, 1, obj->objId.c_str(), (int)obj->objId.length(), SQLITE_STATIC);
  sqlite3_bind_text(stmt, 2, obj->parentId.c_str(), (int)obj->parentId.length(), SQLITE_STATIC);
  sqlite3_bind_text(stmt, 3, obj->name.c_str(), (int)obj->name.length(), SQLITE_STATIC);
  sqlite3_bind_text(stmt, 4, obj->data.c_str(), (int)obj->data.length(), SQLITE_STATIC);

  if (sqlite3_step(stmt) != SQLITE_DONE) {
    sqlite3_finalize(stmt);
    return false;
  }

  sqlite3_finalize(stmt);

  return false;
}

////////////////////////////////////////////////
// updateObject
////////////////////////////////////////////////

bool SQLiteStore::updateObject(Object* obj, Error* err)
{
  sqlite3_stmt* stmt = NULL;

  if (!prepare(FOREMANCC_REGISTRY_SQLITESOTORE_REGISTRY_UPDATE, &stmt))
    return false;

  sqlite3_bind_text(stmt, 1, obj->name.c_str(), (int)obj->name.length(), SQLITE_STATIC);
  sqlite3_bind_text(stmt, 2, obj->data.c_str(), (int)obj->data.length(), SQLITE_STATIC);
  sqlite3_bind_text(stmt, 3, obj->objId.c_str(), (int)obj->objId.length(), SQLITE_STATIC);

  if (sqlite3_step(stmt) != SQLITE_DONE) {
    sqlite3_finalize(stmt);
    return false;
  }

  sqlite3_finalize(stmt);

  return false;
}

////////////////////////////////////////////////
// getObject
////////////////////////////////////////////////

bool SQLiteStore::getObject(const std::string& objId, Error* err)
{
  return false;
}

////////////////////////////////////////////////
// deleteObject
////////////////////////////////////////////////

bool SQLiteStore::deleteObject(const std::string& objId, Error* err)
{
  sqlite3_stmt* stmt = NULL;

  if (!prepare(FOREMANCC_REGISTRY_SQLITESOTORE_REGISTRY_DELETE, &stmt))
    return false;

  sqlite3_bind_text(stmt, 1, objId.c_str(), (int)objId.length(), SQLITE_STATIC);

  if (sqlite3_step(stmt) != SQLITE_DONE) {
    sqlite3_finalize(stmt);
    return false;
  }

  sqlite3_finalize(stmt);

  return false;
}

////////////////////////////////////////////////
// browse
////////////////////////////////////////////////

bool SQLiteStore::browse(Query* q, Objects* objs, Error* err)
{
  return false;
}

////////////////////////////////////////////////
// search
////////////////////////////////////////////////

bool SQLiteStore::search(Query* q, Objects* objs, Error* err)
{
  return false;
}
