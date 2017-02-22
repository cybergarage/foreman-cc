/******************************************************************
 *
 * Foreman for C++
 *
 * Copyright (C) Satoshi Konno 2017
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#ifndef _FOREMANCC_CONST_H_
#define _FOREMANCC_CONST_H_

namespace Round {

#define FOREMANCC_PRODUCT_NAME "foreman"
#define FOREMANCC_CSV_EXPORT_LINE_TERMINATOR "\n"
#define FOREMANCC_DATASOURCE_GRAPHITE "graphite"
#define FOREMANCC_DATASOURCE_RRDTOOL "rrdtool"
#define FOREMANCC_DATASTORE_MEMORY "memory"
#define FOREMANCC_DATASTORE_SQLITE "sqlite"
#define FOREMANCC_DATASTORE_TIMESTAMP_RESOLUTION_SECOND 1
#define FOREMANCC_DATASTORE_TIMESTAMP_RESOLUTION_MINUTE 60
#define FOREMANCC_DATASTORE_TIMESTAMP_RESOLUTION_HOUR 60 * 60
#define FOREMANCC_DATASTORE_TIMESTAMP_RESOLUTION_DAY 60 * 60 * 24
#define FOREMANCC_DATASTORE_PARAM_PROTOCOL "protocol"
#define FOREMANCC_DATASTORE_PARAM_HOST "host"
#define FOREMANCC_FQL_UPDATE "update"
#define FOREMANCC_FQL_SELECT "select"
#define FOREMANCC_FQL_ANALYZE "analyze"
#define FOREMANCC_FQL_OPERATOR_EQUAL "="
#define FOREMANCC_FQL_OPERATOR_LIKE "LIKE"
#define FOREMANCC_FQL_OPERATOR_GT ">"
#define FOREMANCC_FQL_OPERATOR_GE ">="
#define FOREMANCC_FQL_OPERATOR_LT "<"
#define FOREMANCC_FQL_OPERATOR_LE "<="
#define FOREMANCC_HTTP_DEFAULT_PORT 8080
#define FOREMANCC_SQLITESOTORE_FACTOR_TABLE "factor"
#define FOREMANCC_SQLITESOTORE_FACTOR_NAME "name"
#define FOREMANCC_SQLITESOTORE_FACTOR_TABLE_DDL "create table if not exists factor (name text, primary key(name))"
#define FOREMANCC_SQLITESOTORE_FACTOR_INDEX_NAME_DDL "create index if not exists factor_name_idx on factor(name)"
#define FOREMANCC_SQLITESOTORE_FACTOR_INSERT "insert into factor (name) values (?)"
#define FOREMANCC_SQLITESOTORE_FACTOR_SELECT_BY_NAME "select rowid from factor where name = ?"
#define FOREMANCC_SQLITESOTORE_RECORD_TABLE "record"
#define FOREMANCC_SQLITESOTORE_RECORD_ID "id"
#define FOREMANCC_SQLITESOTORE_RECORD_VAL "val"
#define FOREMANCC_SQLITESOTORE_RECORD_TS "ts"
#define FOREMANCC_SQLITESOTORE_RECORD_TABLE_DDL "create table if not exists record (id integer, val real, ts integer, primary key(id,ts))"
#define FOREMANCC_SQLITESOTORE_RECORD_INDEX_ID_DDL "create index if not exists record_id_idx on record(id)"
#define FOREMANCC_SQLITESOTORE_RECORD_INDEX_TS_DDL "create index if not exists record_ts_idx on record(ts)"
#define FOREMANCC_SQLITESOTORE_RECORD_INSERT "insert into record (id, val, ts) values (?, ?, ?)"
#define FOREMANCC_SQLITESOTORE_RECORD_UPDATE "update record set val = ? where id = ? and ts = ?"
#define FOREMANCC_SQLITESOTORE_RECORD_SELECT_BY_TIMESTAMP "select f.name, r.val, r.ts from factor f, record r where f.rowid = r.id and r.ts = ?"
#define FOREMANCC_SQLITESOTORE_RECORD_SELECT_BY_FACTOR "select f.name, r.val, r.ts from factor f, record r where f.rowid = r.id and f.name = ?"
#define FOREMANCC_SQLITESOTORE_RECORD_SELECT_BY_FACTOR_BETWEEN_TIMESTAMP "ts between ? and ?"
#define FOREMANCC_SQLITESOTORE_RECORD_SELECT_ALL "select f.name, r.val, r.ts from factor f, record r where f.rowid = r.id"
#define FOREMANCC_SQLITESOTORE_RECORD_TRUNCATE "delete from record"
}

#endif
