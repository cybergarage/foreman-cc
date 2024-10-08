##################################################################
#
# Foreman for C++
#
# Copyright (C) 2017 Satoshi Konno
#
# This is licensed under BSD-style license, see file COPYING.
#
##################################################################

AC_CONFIG_AUX_DIR(config)
AC_CONFIG_HEADERS(config.h)

AC_INIT([Foreman],[1.0.0])
AC_CONFIG_SRCDIR([include/foreman/Platform.h])
AM_INIT_AUTOMAKE([subdir-objects])

##################################################################
# Constants
##################################################################

SQLITE3_VERSION=3.14.0
ALGLIB_VERSION=3.9.0
UUID_VERSION=1.6.2
CURL_VERSION=7.63.0

BENCHMARK_VERSION=1.1.0

LUA_VERSION=5.2.0

PYTHON_VERSION=2.7.9
JEMALLOC_VERSION=5.1.0

##################################################################
# Checks compiler
##################################################################

AC_PROG_CC
AC_PROG_CXX
AC_PROG_INSTALL
AC_PROG_AWK
AC_PROG_RANLIB

# FIXME : Could not use AX_CXX_COMPILE_STDCXX_11 ...
# AX_CXX_COMPILE_STDCXX_11([noext],[mandatory])
# AX_CHECK_COMPILE_FLAG([-std=c11],[CFLAGS+=" -std=c11"],[AC_MSG_ERROR(Foreman needs C++11 compiler)])

##################################################################
# Check standard header files
##################################################################

AC_CHECK_HEADERS([stdbool.h])

##################################################################
# Check standard libraries
##################################################################

AC_CHECK_LIB([pthread],[main],,[AC_MSG_ERROR(Foreman needs POSIX thread library)])

##################################################################
# Check required libraries
##################################################################

AC_CHECK_HEADERS([sqlite3.h])
AC_CHECK_LIB([sqlite3],[main],,[AC_MSG_ERROR(Foreman needs SQLite $SQLITE3_VERSION later)])

AC_CHECK_LIB([uuid],[main],,[AC_MSG_ERROR(Foreman needs libuuid $UUID_VERSION later)])
AC_CHECK_HEADERS([uuid/uuid.h])

AC_CHECK_HEADERS([curl/curl.h])
AC_CHECK_LIB([curl],[main],,[AC_MSG_ERROR(Foreman needs libcur $CURL_VERSION  laterl)])

##################################################################
# Check option libraries (ALGLIB)
##################################################################

AC_ARG_ENABLE(
  [alglib],
  AS_HELP_STRING([--enable-alglib],[ enable ALGLIB (default = no) ]),
  [case "${enableval}" in
    yes | no ) enable_alglib="${enableval}" ;;
  esac],
  []
)

AM_CONDITIONAL(FOREMAN_ENABLE_ALGLIB,test "$enable_alglib" = yes)
if [ test "$enable_alglib" = yes ]; then
  AC_DEFINE([FOREMAN_ENABLE_ALGLIB],1,[--enable-alglib])
  AC_LANG_PUSH([C++])
  AC_CHECK_HEADERS([libalglib/statistics.h alglib/statistics.h], break)
  AC_LANG_POP([C++])
  AC_CHECK_LIB([alglib],[main],[],[AC_MSG_ERROR([Please install ALGLIB $ALGLIB_VERSION later])],[])ac_cv_lib_alglib=ac_cv_lib_alglib_main

fi

##################################################################
# Check option libraries (Beringei)
##################################################################

AC_ARG_ENABLE(
 	[beringei],
	AS_HELP_STRING([--enable-beringei],[ enable beringei (default = no) ]),
	[case "${enableval}" in
    	yes | no ) enable_beringei="${enableval}" ;;
	esac],
	[]
)

AM_CONDITIONAL(FOREMAN_ENABLE_BERINGEI,test "$enable_beringei" = yes)
if [ test "$enable_beringei" = yes ]; then
	AC_DEFINE([FOREMAN_ENABLE_BERINGEI],1,[--enable-beringei])
	AC_CHECK_LIB([folly],[main],[],[AC_MSG_ERROR([Please install facebook-folly library])],[])ac_cv_lib_folly=ac_cv_lib_folly_main

	AC_CHECK_LIB([gflags],[main],[],[AC_MSG_ERROR([Please install google-gflags library])],[])ac_cv_lib_gflags=ac_cv_lib_gflags_main

	AC_CHECK_LIB([glog],[main],[],[AC_MSG_ERROR([Please install google-glog library])],[])ac_cv_lib_glog=ac_cv_lib_glog_main

	AC_CHECK_LIB([jemalloc],[main],[],[AC_MSG_ERROR([Please install jemalloc library])],[])ac_cv_lib_jemalloc=ac_cv_lib_jemalloc_main

fi

##################################################################
# Check option libraries (Graphite)
##################################################################

AC_ARG_ENABLE(
 	[graphite],
	AS_HELP_STRING([--enable-graphite],[ enable graphite (default = no) ]),
	[case "${enableval}" in
    	yes | no ) enable_graphite="${enableval}" ;;
	esac],
	[]
)

AM_CONDITIONAL(FOREMAN_ENABLE_GRAPHITE,test "$enable_graphite" = yes)
if [ test "$enable_graphite" = yes ]; then
	AC_DEFINE([FOREMAN_ENABLE_GRAPHITE],1,[--enable-graphite])
fi

##################################################################
# Check Language Options
##################################################################

# Python

AC_ARG_ENABLE(
	[script-python],
	[  --enable-script-python enable Python support [default=no]],
	[
		if test $enableval = yes; then
			FOREMAN_SUPPORT_PYTHON=yes
		else
			FOREMAN_SUPPORT_PYTHON=no
		fi
	],[
		FOREMAN_SUPPORT_PYTHON=no
	]
)

if [ test $FOREMAN_SUPPORT_PYTHON = yes ]; then
  AC_CHECK_PROG(FOUND_PYTHON_CONFIG, python-config, yes, no)
  if [ test $FOUND_PYTHON_CONFIG = yes ]; then
    CFLAGS+="`python-config --includes`"
    LIBS+="`python-config --ldflags`"
  else
    AC_CHECK_PROG(FOUND_PYTHON3_CONFIG, python3-config, yes, no)
    if [ test $FOUND_PYTHON3_CONFIG = yes ]; then
      CFLAGS+="`python3-config --includes`"
      LIBS+="`python3-config --ldflags --embed`"
	else
      AC_MSG_ERROR(FOREMAN for C needs Python $PYTHON_VERSION later)
    fi
  fi
  AC_CHECK_HEADERS([Python/Python.h])
  AC_CHECK_HEADERS([Python.h])
  AC_DEFINE([FOREMAN_SUPPORT_PYTHON],1,[Python])
fi

# Lua

AC_ARG_ENABLE(
	[script-lua],
	[  --enable-script-lua	enable Lua support [default=no]],
	[
		if test $enableval = yes; then
			FOREMAN_SUPPORT_LUA=yes
		else
			FOREMAN_SUPPORT_LUA=no
		fi
	],[
		FOREMAN_SUPPORT_LUA=no
	]
)
if [ test $FOREMAN_SUPPORT_LUA = yes ]; then
	FOUND_LUA_LIB=no
	AC_CHECK_HEADERS([lua.h],[main], AC_MSG_ERROR(FOREMAN for C needs LUA $LUA_VERSION later))
	AC_CHECK_LIB([lua],[main],[FOUND_LUA_LIB=yes])
	if [ test $FOUND_LUA_LIB = yes ]; then
       	LIBS+="-llua"
	fi
	if [ test $FOUND_LUA_LIB != yes ]; then
		AC_CHECK_LIB([lua5.2],[main],[FOUND_LUA_LIB=yes])
        	LIBS+="-llua5.2"
	fi
	if [ test $FOUND_LUA_LIB != yes ]; then
		AC_CHECK_LIB([lua5.3],[main],[FOUND_LUA_LIB=yes])
        	LIBS+="-llua5.3"
	fi
	if [ test $FOUND_LUA_LIB != yes ]; then
		AC_MSG_ERROR(FOREMAN for C needs LUA $LUA_VERSION later)
	fi
	AC_DEFINE([FOREMAN_SUPPORT_LUA],1,[Lua])
fi

##################################################################
# Benchmark
##################################################################

AC_ARG_ENABLE(
 	[benchmark],
	AS_HELP_STRING([--enable-benchmark],[ build benchmark (default = no) ]),
	[case "${enableval}" in
    	yes | no ) build_benchmark="${enableval}" ;;
	esac],
	[]
)

AM_CONDITIONAL(FOREMAN_ENABLE_BENCHMARK,test "$build_benchmark" = yes)
if [ test "$build_benchmark" = yes ]; then
	AC_CHECK_HEADERS([benchmark/benchmark.h])
	AC_CHECK_LIB([benchmark],[main],,[AC_MSG_ERROR(Foreman needs Google Benchmark $BENCHMARK_VERSION later)])
fi

##################################################################
# Debug
##################################################################

AC_ARG_ENABLE(
 	[debug],
	AS_HELP_STRING([--enable-debug],[enable debugging (default = no)]),
	[case "${enableval}" in
    	yes | no ) enable_debug ="${enableval}" ;;
	esac],
	[]
)

if [ test "$enable_debug" = yes ]; then
	AC_DEFINE([DEBUG],1,[Define to 1 if you want to debug])
fi

##################################################################
# Testing
##################################################################

AC_ARG_ENABLE(
 	[test],
	AS_HELP_STRING([--enable-test],[ build tests (default = no) ]),
	[case "${enableval}" in
    	yes | no ) build_test="${enableval}" ;;
	esac],
	[]
)

AM_CONDITIONAL(FOREMAN_ENABLE_TESTS,test "$build_test" = yes)
if [ test "$build_test" = yes ]; then
	AC_CHECK_LIB([boost_system-mt],[main],,
		[AC_CHECK_LIB([boost_system],[main],,[AC_MSG_ERROR(Foreman needs boost::system-mt)])])

	AC_CHECK_LIB([boost_filesystem-mt],[main],,
		[AC_CHECK_LIB([boost_filesystem],[main],,[AC_MSG_ERROR(Foreman needs boost::filesystem-mt)])])

	AC_CHECK_LIB([boost_thread-mt],[main],,
		[AC_CHECK_LIB([boost_thread],[main],,[AC_MSG_ERROR(Foreman needs boost::thread-mt)])])

	AC_CHECK_LIB([boost_unit_test_framework-mt],[main],,
		[AC_CHECK_LIB([boost_unit_test_framework],[main],,[AC_MSG_ERROR(Foreman needs boost::boost_unit_test_framework)])])
fi

##################################################################
# Makefiles
##################################################################

AC_CONFIG_FILES([
Makefile
include/Makefile
lib/Makefile
lib/unix/Makefile
bin/Makefile
bin/foremanbench/Makefile
bin/foremanbench/unix/Makefile
bin/foremanusage/Makefile
bin/foremanusage/unix/Makefile
test/Makefile
test/unix/Makefile
])
AC_OUTPUT

