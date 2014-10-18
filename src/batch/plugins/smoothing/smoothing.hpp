#ifndef rstools_rsbatch_plugins_smoothing_smoothing_h
#define rstools_rsbatch_plugins_smoothing_smoothing_h

#include "rscommon.h"
#include "batch/util/plugin.hpp"
#include "tool/smoothing.hpp"
#include "task/smoothing.hpp"

using namespace rstools::batch::util;

namespace rstools {
namespace batch {
namespace plugins {
namespace smoothing {

class Smoothing : Plugin {

    public:
        Smoothing();
        void  registerPlugin();
        const char* getName();
        const char* getCode();
        const char* getVersion();

        static RSTool* createSmoothingTool();
        static RSTask* createSmoothingTask();
        
    protected:
        rsToolRegistration* createSmoothingToolRegistration();
        rsXSDExtension* createSmoothingToolXSDExtension();
};

}}}} // namespace rstools::batch::plugins::smoothing

extern "C" {
    G_MODULE_EXPORT Plugin* rsGetPlugin(void);
}

#endif
