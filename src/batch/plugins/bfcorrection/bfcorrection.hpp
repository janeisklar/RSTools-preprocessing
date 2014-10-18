#ifndef rstools_rsbatch_plugins_bfcorrection_bfcorrection_h
#define rstools_rsbatch_plugins_bfcorrection_bfcorrection_h

#include "rscommon.h"
#include "batch/util/plugin.hpp"
#include "tool/bfcorrection.hpp"
#include "task/bfcorrection.hpp"

using namespace rstools::batch::util;

namespace rstools {
namespace batch {
namespace plugins {
namespace bfcorrection {

class BFCorrection : Plugin {

    public:
        BFCorrection();
        void  registerPlugin();
        const char* getName();
        const char* getCode();
        const char* getVersion();

        static RSTool* createBFCorrectionTool();
        static RSTask* createBFCorrectionTask();
        
    protected:
        rsToolRegistration* createBFCorrectionToolRegistration();
        rsXSDExtension* createBFCorrectionToolXSDExtension();
};

}}}} // namespace rstools::batch::plugins::bfcorrection

extern "C" {
    G_MODULE_EXPORT Plugin* rsGetPlugin(void);
}

#endif
