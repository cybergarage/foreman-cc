##################################################################
#
# Foreman for C++
#
# Copyright (C) Satoshi Konno 2017
#
# This is licensed under BSD-style license, see file COPYING.
#
##################################################################

AC_CONFIG_AUX_DIR(config)
AM_CONFIG_HEADER(config.h)

AC_INIT([Foreman], [0.1])
AC_CONFIG_SRCDIR([include/foreman/memstore.h])
AM_INIT_AUTOMAKE([subdir-objects])

##############################
# Constants
##############################

SQLITE3_VERSION=3.14.0

##############################
# Checks compiler
##############################

AC_PROG_CC
AC_PROG_CXX
AC_PROG_INSTALL
AC_PROG_AWK
AC_PROG_RANLIB

##############################
# Check standard header files
##############################

AC_CHECK_HEADERS([stdbool.h])

##############################
# Check standard libraries
##############################

AC_CHECK_LIB([pthread],[main],,[AC_MSG_ERROR(Foreman needs POSIX thread library)])

##############################
# Check libraries
##############################

AC_CHECK_HEADERS([sqlite3.h])
AC_CHECK_LIB([sqlite3],[main],,[AC_MSG_ERROR(Foreman needs SQLite $SQLITE3_VERSION later)])

##############################
# Testing
##############################

AC_ARG_ENABLE(
 	[tests],
	AC_HELP_STRING([--enable-tests], [ build tests (default = no) ]),
	[case "${enableval}" in
    	yes | no ) build_tests="${enableval}" ;;
	esac],
	[]
)

AM_CONDITIONAL(FOREMAN_ENABLE_TESTS,test "$build_tests" = yes)
if [ test "$build_tests" = yes ]; then
	AC_CHECK_LIB([boost_system-mt],[main],,
		[AC_CHECK_LIB([boost_system],[main],,[AC_MSG_ERROR(Foreman needs boost::system-mt)])])

	AC_CHECK_LIB([boost_filesystem-mt],[main],,
		[AC_CHECK_LIB([boost_filesystem],[main],,[AC_MSG_ERROR(Foreman needs boost::filesystem-mt)])])

	AC_CHECK_LIB([boost_thread-mt],[main],,
		[AC_CHECK_LIB([boost_thread],[main],,[AC_MSG_ERROR(Foreman needs boost::thread-mt)])])

	AC_CHECK_LIB([boost_unit_test_framework-mt],[main],,
		[AC_CHECK_LIB([boost_unit_test_framework],[main],,[AC_MSG_ERROR(Foreman needs boost::boo
st_unit_test_framework)])])
fi

##############################
# Makefiles
##############################

AC_OUTPUT([
Makefile
include/Makefile
lib/Makefile
lib/unix/Makefile
bin/Makefile
bin/foremanbench/Makefile
bin/foremanbench/unix/Makefile
tests/Makefile
tests/unix/Makefile
])
