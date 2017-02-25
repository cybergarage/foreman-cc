##################################################################
#
# Foreman for C++
#
# Copyright (C) Satoshi Konno 2017
#
# This is licensed under BSD-style license, see file COPYING.
#
##################################################################

bin_PROGRAMS = foremanusage

AM_CPPFLAGS = -I$(top_srcdir)/include -I$(top_srcdir)/src -I../

foremanusage_SOURCES = \
	..//foremanusage.cpp

foremanusage_LDADD = ../../../lib/unix/libforeman++.a
