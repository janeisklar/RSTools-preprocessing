#ifndef rstools_rsbatch_plugins_despiking_despiking_h
#define rstools_rsbatch_plugins_despiking_despiking_h

#include "rscommon.h"
#include "batch/util/plugin.hpp"
#include "tool/despiking.hpp"
#include "task/despiking.hpp"

using namespace rstools::batch::util;

namespace rstools {
namespace batch {
namespace plugins {
namespace despiking {

class Despiking : Plugin {

    public:
        Despiking();
        void  registerPlugin();
        const char* getName();
        const char* getCode();
        const char* getVersion();

        static RSTool* createDespikingTool();
        static RSTask* createDespikingTask();
        
    protected:
        rsToolRegistration* createDespikingToolRegistration();
        rsXSDExtension* createDespikingToolXSDExtension();
};

}}}} // namespace rstools::batch::plugins::despiking

extern "C" {
    G_MODULE_EXPORT Plugin* rsGetPlugin(void);
}

#endif
