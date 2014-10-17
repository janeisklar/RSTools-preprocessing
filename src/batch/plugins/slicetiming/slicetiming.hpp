#ifndef rstools_rsbatch_plugins_slicetiming_slicetiming_h
#define rstools_rsbatch_plugins_slicetiming_slicetiming_h

#include "rscommon.h"
#include "batch/util/plugin.hpp"
#include "tool/slicetiming.hpp"
#include "task/slicetiming.hpp"

using namespace rstools::batch::util;

namespace rstools {
namespace batch {
namespace plugins {
namespace slicetiming {

class SliceTiming : Plugin {

    public:
        SliceTiming();
        void  registerPlugin();
        const char* getName();
        const char* getCode();
        const char* getVersion();

        static RSTool* createSliceTimingTool();
        static RSTask* createSliceTimingTask();
        static RSTool* createMBSliceTimingTool();
        static RSTask* createMBSliceTimingTask();
        
    protected:
        rsToolRegistration* createSliceTimingToolRegistration();
        rsXSDExtension* createSliceTimingToolXSDExtension();
        rsToolRegistration* createMBSliceTimingToolRegistration();
        rsXSDExtension* createMBSliceTimingToolXSDExtension();
};

}}}} // namespace rstools::batch::plugins::slicetiming

extern "C" {
    G_MODULE_EXPORT Plugin* rsGetPlugin(void);
}

#endif
