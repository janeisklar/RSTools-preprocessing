AUTOMAKE_OPTIONS = subdir-objects

AM_CFLAGS = -DDATA_PATH=\"$(datadir)\" -I$(top_srcdir)/src
AM_CPPFLAGS = -DDATA_PATH=\"$(datadir)\" -I$(top_srcdir)/src

lib_LTLIBRARIES =              \
	libSliceTimingPlugin.la    \
	libDespikingPlugin.la      \
	libBFCorrectionPlugin.la

libSliceTimingPlugin_la_SOURCES = slicetiming/task/mbslicetiming.cpp slicetiming/task/slicetiming.cpp slicetiming/tool/slicetiming.cpp slicetiming/slicetiming.cpp
libSliceTimingPlugin_la_LIBADD  = $(LDADD) @LIBOBJS@
libSliceTimingPlugin_la_LDFLAGS = -module -export-dynamic

libDespikingPlugin_la_SOURCES = despiking/task/despiking.cpp despiking/tool/despiking.cpp despiking/despiking.cpp
libDespikingPlugin_la_LIBADD  = $(LDADD) @LIBOBJS@
libDespikingPlugin_la_LDFLAGS = -module -export-dynamic

libBFCorrectionPlugin_la_SOURCES = bfcorrection/task/bfcorrection.cpp bfcorrection/tool/bfcorrection.cpp bfcorrection/bfcorrection.cpp
libBFCorrectionPlugin_la_LIBADD  = $(LDADD) @LIBOBJS@
libBFCorrectionPlugin_la_LDFLAGS = -module -export-dynamic

pluginsdir = $(datadir)/rstools/plugins
plugins_DATA = \
	.libs/libSliceTimingPlugin.so   \
	.libs/libDespikingPlugin.so     \
	.libs/libBFCorrectionPlugin.so

jobpluginsdir = $(datadir)/$(PACKAGE)/jobs/plugins
jobplugins_DATA =                                     \
	../../../share/jobs/plugins/slicetiming.xsdext    \
	../../../share/jobs/plugins/mbslicetiming.xsdext  \
	../../../share/jobs/plugins/despiking.xsdext      \
	../../../share/jobs/plugins/bfcorrection.xsdext
