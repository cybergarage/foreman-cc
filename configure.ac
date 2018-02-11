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
AM_CONFIG_HEADER(config.h)

AC_INIT([Foreman], [0.1])
AC_CONFIG_SRCDIR([include/foreman/Platform.h])
AM_INIT_AUTOMAKE([subdir-objects])

##################################################################
# Constants
##################################################################

SQLITE3_VERSION=3.14.0
BENCHMARK_VERSION=1.1.0

LUA_VERSION=5.2.0
PYTHON_VERSION=2.7.9

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

##################################################################
# Check option libraries
##################################################################

AC_CHECK_LIB([uuid],[main])
AC_CHECK_HEADERS([uuid/uuid.h])

##################################################################
# Check option libraries (Beringei)
##################################################################

AC_ARG_ENABLE(
 	[beringei],
	AC_HELP_STRING([--enable-beringei], [ enable beringei (default = no) ]),
	[case "${enableval}" in
    	yes | no ) eneble_beringei="${enableval}" ;;
	esac],
	[]
)

AM_CONDITIONAL(FOREMAN_ENABLE_BERINGEI,test "$eneble_beringei" = yes)
if [ test "$eneble_beringei" = yes ]; then
	AC_DEFINE([FOREMAN_ENABLE_BERINGEI],1,[--enable-beringei])
	AC_HAVE_LIBRARY([folly],,[AC_MSG_ERROR([Please install facebook-folly library])])
	AC_HAVE_LIBRARY([gflags],,[AC_MSG_ERROR([Please install google-gflags library])])
	AC_HAVE_LIBRARY([glog],,[AC_MSG_ERROR([Please install google-glog library])])
fi

##################################################################
# Check option libraries (Graphite)
##################################################################

AC_ARG_ENABLE(
 	[graphite],
	AC_HELP_STRING([--enable-graphite], [ enable graphite (default = no) ]),
	[case "${enableval}" in
    	yes | no ) eneble_graphite="${enableval}" ;;
	esac],
	[]
)

AM_CONDITIONAL(FOREMAN_ENABLE_GRAPHITE,test "$eneble_graphite" = yes)
if [ test "$eneble_graphite" = yes ]; then
	AC_DEFINE([FOREMAN_ENABLE_GRAPHITE],1,[--enable-graphite])
	AC_CHECK_HEADERS([curl/curl.h])
	AC_CHECK_LIB([curl],[main],,[AC_MSG_ERROR(Foreman needs libcurl)])
fi

##############################
# Check Language Options
##############################

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
  if [ test $FOUND_PYTHON_CONFIG != yes ]; then
    AC_MSG_ERROR(FOREMAN for C needs Python $PYTHON_VERSION later)
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
	AC_CHECK_HEADERS([lua.h])
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
	AC_HELP_STRING([--enable-benchmark], [ build benchmark (default = no) ]),
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
# Testing
##################################################################

AC_ARG_ENABLE(
 	[test],
	AC_HELP_STRING([--enable-test], [ build tests (default = no) ]),
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

AC_OUTPUT([
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

