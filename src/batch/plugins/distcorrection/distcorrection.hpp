#ifndef rstools_rsbatch_plugins_distcorrection_distcorrection_h
#define rstools_rsbatch_plugins_distcorrection_distcorrection_h

#include "rscommon.h"
#include "batch/util/plugin.hpp"
#include "tool/distcorrection.hpp"
#include "task/distcorrection.hpp"

using namespace rstools::batch::util;

namespace rstools {
namespace batch {
namespace plugins {
namespace distcorrection {

class Distcorrection : Plugin {

    public:
        Distcorrection();
        void  registerPlugin();
        const char* getName();
        const char* getCode();
        const char* getFMName();
        const char* getFMCode();
        const char* getVersion();

        static RSTool* createDistcorrectionTool();
        static RSTask* createDistcorrectionTask();
        static RSTool* createFMDistcorrectionTool();
        static RSTask* createFMDistcorrectionTask();
        
    protected:
        rsToolRegistration* createDistcorrectionToolRegistration();
        rsXSDExtension* createDistcorrectionToolXSDExtension();
        rsToolRegistration* createFMDistcorrectionToolRegistration();
        rsXSDExtension* createFMDistcorrectionToolXSDExtension();
};

}}}} // namespace rstools::batch::plugins::distcorrection

extern "C" {
    G_MODULE_EXPORT Plugin* rsGetPlugin(void);
}

#endif
