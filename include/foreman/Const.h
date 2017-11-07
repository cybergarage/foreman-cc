/******************************************************************
 *
 * Foreman for C++
 *
 * Copyright (C) 2017 Satoshi Konno
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#ifndef _FOREMANCC_CONST_H_
#define _FOREMANCC_CONST_H_

namespace Foreman {

#define FOREMANCC_PRODUCT_NAME "foreman"
#define FOREMANCC_PRODUCT_VERSION "0.1"
#define FOREMANCC_CSV_EXPORT_LINE_TERMINATOR "\n"
#define FOREMANCC_DATASOURCE_GRAPHITE "graphite"
#define FOREMANCC_DATASOURCE_RRDTOOL "rrdtool"
#define FOREMANCC_HTTP_DEFAULT_PORT 8080
#define FOREMANCC_REGISTRY_ROOT_OBJECT_ID "0"
#define FOREMANCC_REGISTRY_SQLITESOTORE_REGISTRY_TABLE "registry"
#define FOREMANCC_REGISTRY_SQLITESOTORE_REGISTRY_TABLE_DDL "create table if not exists registry (id text, name text, pid text, data text, primary key(id))"
#define FOREMANCC_REGISTRY_SQLITESOTORE_REGISTRY_CREATE "insert into registry (id, pid, name, data) values (?, ?, ?, ?)"
#define FOREMANCC_REGISTRY_SQLITESOTORE_REGISTRY_UPDATE "update registry set name = ?, data = ? where id = ?"
#define FOREMANCC_REGISTRY_SQLITESOTORE_REGISTRY_DELETE "delete from registry where id = ?"
#define FOREMANCC_REGISTRY_SQLITESOTORE_REGISTRY_SELECT_BY_ID "select id, name, pid, data from factor where id = ?"
#define FOREMANCC_REGISTRY_SQLITESOTORE_REGISTRY_SELECT_BY_PARENTID "select id, name, pid, data from factor where pid = ?"
#define FOREMANCC_REGISTRY_SQLITESOTORE_REGISTRY_TRUNCATE "delete from registry"
#define FOREMANCC_METRIC_DATASTORE_MEMORY "memory"
#define FOREMANCC_METRIC_DATASTORE_SQLITE "sqlite"
#define FOREMANCC_METRIC_DATASTORE_TIMESTAMP_RESOLUTION_SECOND 1
#define FOREMANCC_METRIC_DATASTORE_TIMESTAMP_RESOLUTION_MINUTE 60
#define FOREMANCC_METRIC_DATASTORE_TIMESTAMP_RESOLUTION_HOUR 60 * 60
#define FOREMANCC_METRIC_DATASTORE_TIMESTAMP_RESOLUTION_DAY 60 * 60 * 24
#define FOREMANCC_METRIC_DATASTORE_PARAM_PROTOCOL "protocol"
#define FOREMANCC_METRIC_DATASTORE_PARAM_HOST "host"
#define FOREMANCC_METRIC_STORE_DEFAULT_RETENTIONI_INTERVAL 300
#define FOREMANCC_METRIC_SQLITESOTORE_FACTOR_TABLE "factor"
#define FOREMANCC_METRIC_SQLITESOTORE_FACTOR_NAME "name"
#define FOREMANCC_METRIC_SQLITESOTORE_FACTOR_TABLE_DDL "create table if not exists factor (name text, primary key(name))"
#define FOREMANCC_METRIC_SQLITESOTORE_FACTOR_INDEX_NAME_DDL "create index if not exists factor_name_idx on factor(name)"
#define FOREMANCC_METRIC_SQLITESOTORE_FACTOR_INSERT "insert into factor (name) values (?)"
#define FOREMANCC_METRIC_SQLITESOTORE_FACTOR_SELECT_BY_NAME "select rowid from factor where name = ?"
#define FOREMANCC_METRIC_SQLITESOTORE_RECORD_TABLE "record"
#define FOREMANCC_METRIC_SQLITESOTORE_RECORD_ID "id"
#define FOREMANCC_METRIC_SQLITESOTORE_RECORD_VAL "val"
#define FOREMANCC_METRIC_SQLITESOTORE_RECORD_TS "ts"
#define FOREMANCC_METRIC_SQLITESOTORE_RECORD_TABLE_DDL "create table if not exists record (id integer, val real, ts integer, primary key(id,ts))"
#define FOREMANCC_METRIC_SQLITESOTORE_RECORD_INDEX_ID_DDL "create index if not exists record_id_idx on record(id)"
#define FOREMANCC_METRIC_SQLITESOTORE_RECORD_INDEX_TS_DDL "create index if not exists record_ts_idx on record(ts)"
#define FOREMANCC_METRIC_SQLITESOTORE_RECORD_INSERT "insert into record (id, val, ts) values (?, ?, ?)"
#define FOREMANCC_METRIC_SQLITESOTORE_RECORD_UPDATE "update record set val = ? where id = ? and ts = ?"
#define FOREMANCC_METRIC_SQLITESOTORE_RECORD_SELECT_BY_TIMESTAMP "select f.name, r.val, r.ts from factor f, record r where f.rowid = r.id and r.ts = ?"
#define FOREMANCC_METRIC_SQLITESOTORE_RECORD_SELECT_BY_FACTOR "select f.name, r.val, r.ts from factor f, record r where f.rowid = r.id and f.name = ?"
#define FOREMANCC_METRIC_SQLITESOTORE_RECORD_SELECT_BY_FACTOR_BETWEEN_TIMESTAMP "select f.name, r.val, r.ts from factor f, record r where f.rowid = r.id and f.name = ? and ts between ? and ?"
#define FOREMANCC_METRIC_SQLITESOTORE_RECORD_SELECT_ALL "select f.name, r.val, r.ts from factor f, record r where f.rowid = r.id"
#define FOREMANCC_METRIC_SQLITESOTORE_RECORD_TRUNCATE "delete from record"
#define FOREMANCC_FQL_UPDATE "update"
#define FOREMANCC_FQL_SELECT "select"
#define FOREMANCC_FQL_ANALYZE "analyze"
#define FOREMANCC_FQL_OPERATOR_EQUAL "="
#define FOREMANCC_FQL_OPERATOR_LIKE "LIKE"
#define FOREMANCC_FQL_OPERATOR_GT ">"
#define FOREMANCC_FQL_OPERATOR_GE ">="
#define FOREMANCC_FQL_OPERATOR_LT "<"
#define FOREMANCC_FQL_OPERATOR_LE "<="
}

#endif
