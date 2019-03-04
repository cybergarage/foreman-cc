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
#define FOREMANCC_PRODUCT_VERSION "0.8.6"
#define FOREMANCC_DEFAULT_SERVER_HOST "localhost"
#define FOREMANCC_DEFAULT_RPC_PORT 8188
#define FOREMANCC_REGISTRY_ROOT_OBJECT_ID "0"
#define FOREMANCC_REGISTRY_PROPERTIES_DELIM 7
#define FOREMANCC_REGISTRY_PROPERTY_DELIM 9
#define FOREMANCC_METRIC_DATASTORE_TIMESTAMP_RESOLUTION_SECOND 1
#define FOREMANCC_METRIC_DATASTORE_TIMESTAMP_RESOLUTION_MINUTE 60
#define FOREMANCC_METRIC_DATASTORE_TIMESTAMP_RESOLUTION_HOUR 60 * 60
#define FOREMANCC_METRIC_DATASTORE_TIMESTAMP_RESOLUTION_DAY 60 * 60 * 24
#define FOREMANCC_METRIC_STORE_DEFAULT_RETENTIONI_INTERVAL 300
#define FOREMANCC_HTTP_REQUEST_FQL_PATH "/fql"
#define FOREMANCC_HTTP_REQUEST_FQL_QUERY_PARAM "q"
#define FOREMANCC_ACTION_SCRIPT_ENCORDING_NONE 0
#define FOREMANCC_ACTION_SCRIPT_ENCORDING_BASE64 1
#define FOREMANCC_ACTION_SCRIPT_ENGINE_SYSTEM "system"
#define FOREMANCC_ACTION_SCRIPT_ENGINE_PYTHON "python"
#define FOREMANCC_ACTION_SCRIPT_ENGINE_LUA "lua"
#define FOREMANCC_SYSTEM_FUNCTION_SETREGISTER "set_register"
#define FOREMANCC_SYSTEM_FUNCTION_GETREGISTER "get_register"
#define FOREMANCC_SYSTEM_FUNCTION_REMOVEREGISTER "remove_register"
#define FOREMANCC_SYSTEM_FUNCTION_EXECUTEQUERY "execute_query"
#define FOREMANCC_SYSTEM_FUNCTION_POSTQUERY "post_query"
#define FOREMANCC_SYSTEM_FUNCTION_LOG "log"
#define FOREMANCC_FQL_UPDATE "update"
#define FOREMANCC_FQL_SELECT "select"
#define FOREMANCC_FQL_ANALYZE "analyze"
#define FOREMANCC_FQL_OPERATOR_EQUAL "="
#define FOREMANCC_FQL_OPERATOR_LIKE "LIKE"
#define FOREMANCC_FQL_OPERATOR_GT ">"
#define FOREMANCC_FQL_OPERATOR_GE ">="
#define FOREMANCC_FQL_OPERATOR_LT "<"
#define FOREMANCC_FQL_OPERATOR_LE "<="
#define FOREMANCC_LOGGER_LEVEL_ALL 0
#define FOREMANCC_LOGGER_LEVEL_DEBUG 0
#define FOREMANCC_LOGGER_LEVEL_TRACE 1
#define FOREMANCC_LOGGER_LEVEL_INFO 2
#define FOREMANCC_LOGGER_LEVEL_WARN 3
#define FOREMANCC_LOGGER_LEVEL_ERROR 4
#define FOREMANCC_LOGGER_LEVEL_FATAL 5
#define FOREMANCC_LOGGER_LEVEL_NONE 6
#define FOREMANCC_LOGGER_LEVEL_STRING_DEBUG "DEBUG"
#define FOREMANCC_LOGGER_LEVEL_STRING_TRACE "TRACE"
#define FOREMANCC_LOGGER_LEVEL_STRING_INFO "INFO"
#define FOREMANCC_LOGGER_LEVEL_STRING_WARN "WARN"
#define FOREMANCC_LOGGER_LEVEL_STRING_ERROR "ERROR"
#define FOREMANCC_LOGGER_LEVEL_STRING_FATAL "FATAL"

}

#endif
