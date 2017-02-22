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

#define FORMANCC_PRODUCT_NAME "foreman"
#define FORMANCC_MODULE_NAME "foreman-py"
#define FORMANCC_CSV_EXPORT_LINE_TERMINATOR "\n"
#define FORMANCC_DATASOURCE_GRAPHITE "graphite"
#define FORMANCC_DATASOURCE_RRDTOOL "rrdtool"
#define FORMANCC_DATASTORE_MEMORY "memory"
#define FORMANCC_DATASTORE_SQLITE "sqlite"
#define FORMANCC_DATASTORE_TIMESTAMP_RESOLUTION_SECOND 1
#define FORMANCC_DATASTORE_TIMESTAMP_RESOLUTION_MINUTE 60
#define FORMANCC_DATASTORE_TIMESTAMP_RESOLUTION_HOUR 60 * 60
#define FORMANCC_DATASTORE_TIMESTAMP_RESOLUTION_DAY 60 * 60 * 24
#define FORMANCC_DATASTORE_PARAM_PROTOCOL "protocol"
#define FORMANCC_DATASTORE_PARAM_HOST "host"
#define FORMANCC_CQL_UPDATE "update"
#define FORMANCC_CQL_SELECT "select"
#define FORMANCC_CQL_ANALYZE "analyze"
#define FORMANCC_CQL_OPERATOR_EQUAL "="
#define FORMANCC_CQL_OPERATOR_LIKE "LIKE"
#define FORMANCC_CQL_OPERATOR_GT ">"
#define FORMANCC_CQL_OPERATOR_GE ">="
#define FORMANCC_CQL_OPERATOR_LT "<"
#define FORMANCC_CQL_OPERATOR_LE "<="
#define FORMANCC_HTTP_DEFAULT_PORT 8080
}

#endif
