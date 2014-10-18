#ifndef rstools_rsbatch_plugins_realignment_realignment_h
#define rstools_rsbatch_plugins_realignment_realignment_h

#include "rscommon.h"
#include "batch/util/plugin.hpp"
#include "tool/realignment.hpp"
#include "task/realignment.hpp"

using namespace rstools::batch::util;

namespace rstools {
namespace batch {
namespace plugins {
namespace realignment {

class Realignment : Plugin {

    public:
        Realignment();
        void  registerPlugin();
        const char* getName();
        const char* getCode();
        const char* getVersion();

        static RSTool* createRealignmentTool();
        static RSTask* createRealignmentTask();
        
    protected:
        rsToolRegistration* createRealignmentToolRegistration();
        rsXSDExtension* createRealignmentToolXSDExtension();
};

}}}} // namespace rstools::batch::plugins::realignment

extern "C" {
    G_MODULE_EXPORT Plugin* rsGetPlugin(void);
}

#endif
