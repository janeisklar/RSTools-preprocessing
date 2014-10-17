AUTOMAKE_OPTIONS = subdir-objects

AM_CFLAGS = -DDATA_PATH=\"$(datadir)\" -I$(top_srcdir)/src
AM_CPPFLAGS = -DDATA_PATH=\"$(datadir)\" -I$(top_srcdir)/src

lib_LTLIBRARIES = \
	libSliceTimingPlugin.la

libSliceTimingPlugin_la_SOURCES = slicetiming/task/slicetiming.cpp slicetiming/tool/slicetiming.cpp slicetiming/slicetiming.cpp
libSliceTimingPlugin_la_LIBADD  = $(LDADD) @LIBOBJS@
libSliceTimingPlugin_la_LDFLAGS = -module -export-dynamic

pluginsdir = $(datadir)/rstools/plugins
plugins_DATA = \
	.libs/libSliceTimingPlugin.so

jobpluginsdir = $(datadir)/$(PACKAGE)/jobs/plugins
jobplugins_DATA = \
	../../../share/jobs/plugins/slicetiming.xsdext
