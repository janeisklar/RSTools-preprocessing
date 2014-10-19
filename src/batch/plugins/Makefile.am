AUTOMAKE_OPTIONS = subdir-objects

AM_CFLAGS = -DDATA_PATH=\"$(datadir)\" -I$(top_srcdir)/src
AM_CPPFLAGS = -DDATA_PATH=\"$(datadir)\" -I$(top_srcdir)/src

lib_LTLIBRARIES =                    \
	libSliceTimingPlugin.la          \
	libDespikingPlugin.la            \
	libBFCorrectionPlugin.la         \
	libRealignmentPlugin.la          \
	libReorientationPlugin.la        \
	libSmoothingPlugin.la            \
	libDistortionCorrectionPlugin.la \
	libMergeRegressorsPlugin.la      \
	libNormalizationPlugin.la

libSliceTimingPlugin_la_SOURCES = slicetiming/task/mbslicetiming.cpp slicetiming/task/slicetiming.cpp slicetiming/tool/slicetiming.cpp slicetiming/slicetiming.cpp
libSliceTimingPlugin_la_LIBADD  = $(LDADD) @LIBOBJS@
libSliceTimingPlugin_la_LDFLAGS = -module -export-dynamic

libDespikingPlugin_la_SOURCES = despiking/task/despiking.cpp despiking/tool/despiking.cpp despiking/despiking.cpp
libDespikingPlugin_la_LIBADD  = $(LDADD) @LIBOBJS@
libDespikingPlugin_la_LDFLAGS = -module -export-dynamic

libBFCorrectionPlugin_la_SOURCES = bfcorrection/task/bfcorrection.cpp bfcorrection/tool/bfcorrection.cpp bfcorrection/bfcorrection.cpp
libBFCorrectionPlugin_la_LIBADD  = $(LDADD) @LIBOBJS@
libBFCorrectionPlugin_la_LDFLAGS = -module -export-dynamic

libRealignmentPlugin_la_SOURCES = realignment/task/realignment.cpp realignment/tool/realignment.cpp realignment/realignment.cpp
libRealignmentPlugin_la_LIBADD  = $(LDADD) @LIBOBJS@
libRealignmentPlugin_la_LDFLAGS = -module -export-dynamic

libReorientationPlugin_la_SOURCES = reorientation/task/reorientation.cpp reorientation/tool/reorientation.cpp reorientation/reorientation.cpp
libReorientationPlugin_la_LIBADD  = $(LDADD) @LIBOBJS@
libReorientationPlugin_la_LDFLAGS = -module -export-dynamic

libSmoothingPlugin_la_SOURCES = smoothing/task/smoothing.cpp smoothing/tool/smoothing.cpp smoothing/smoothing.cpp
libSmoothingPlugin_la_LIBADD  = $(LDADD) @LIBOBJS@
libSmoothingPlugin_la_LDFLAGS = -module -export-dynamic

libDistortionCorrectionPlugin_la_SOURCES = distcorrection/task/distcorrection.cpp distcorrection/tool/distcorrection.cpp distcorrection/distcorrection.cpp
libDistortionCorrectionPlugin_la_LIBADD  = $(LDADD) @LIBOBJS@
libDistortionCorrectionPlugin_la_LDFLAGS = -module -export-dynamic

libMergeRegressorsPlugin_la_SOURCES = regressors/task/regressors.cpp regressors/tool/regressors.cpp regressors/regressors.cpp
libMergeRegressorsPlugin_la_LIBADD  = $(LDADD) @LIBOBJS@
libMergeRegressorsPlugin_la_LDFLAGS = -module -export-dynamic

libNormalizationPlugin_la_SOURCES = normalization/task/normalization.cpp normalization/tool/normalization.cpp normalization/normalization.cpp
libNormalizationPlugin_la_LIBADD  = $(LDADD) @LIBOBJS@
libNormalizationPlugin_la_LDFLAGS = -module -export-dynamic

pluginsdir = $(datadir)/rstools/plugins
plugins_DATA =                             \
	.libs/libSliceTimingPlugin.so          \
	.libs/libDespikingPlugin.so            \
	.libs/libBFCorrectionPlugin.so         \
	.libs/libRealignmentPlugin.so          \
	.libs/libReorientationPlugin.so        \
	.libs/libSmoothingPlugin.so            \
	.libs/libDistortionCorrectionPlugin.so \
	.libs/libMergeRegressorsPlugin.so      \
	.libs/libNormalizationPlugin.so

jobpluginsdir = $(datadir)/$(PACKAGE)/jobs/plugins
jobplugins_DATA =                                     \
	../../../share/jobs/plugins/slicetiming.xsdext    \
	../../../share/jobs/plugins/mbslicetiming.xsdext  \
	../../../share/jobs/plugins/despiking.xsdext      \
	../../../share/jobs/plugins/bfcorrection.xsdext   \
	../../../share/jobs/plugins/realignment.xsdext    \
	../../../share/jobs/plugins/reorientation.xsdext  \
	../../../share/jobs/plugins/smoothing.xsdext      \
	../../../share/jobs/plugins/distcorrection.xsdext \
	../../../share/jobs/plugins/regressors.xsdext     \
	../../../share/jobs/plugins/normalization.xsdext
