#ifndef rstools_rsbatch_plugins_regressors_regressors_h
#define rstools_rsbatch_plugins_regressors_regressors_h

#include "rscommon.h"
#include "batch/util/plugin.hpp"
#include "tool/regressors.hpp"
#include "task/regressors.hpp"

using namespace rstools::batch::util;

namespace rstools {
namespace batch {
namespace plugins {
namespace regressors {

class Regressors : Plugin {

    public:
        Regressors();
        void  registerPlugin();
        const char* getName();
        const char* getCode();
        const char* getVersion();

        static RSTool* createRegressorsTool();
        static RSTask* createRegressorsTask();
        
    protected:
        rsToolRegistration* createRegressorsToolRegistration();
        rsXSDExtension* createRegressorsToolXSDExtension();
};

}}}} // namespace rstools::batch::plugins::regressors

extern "C" {
    G_MODULE_EXPORT Plugin* rsGetPlugin(void);
}

#endif
