#ifndef rstools_rsbatch_plugins_reorientation_reorientation_h
#define rstools_rsbatch_plugins_reorientation_reorientation_h

#include "rscommon.h"
#include "batch/util/plugin.hpp"
#include "tool/reorientation.hpp"
#include "task/reorientation.hpp"

using namespace rstools::batch::util;

namespace rstools {
namespace batch {
namespace plugins {
namespace reorientation {

class Reorientation : Plugin {

    public:
        Reorientation();
        void  registerPlugin();
        const char* getName();
        const char* getCode();
        const char* getVersion();

        static RSTool* createReorientationTool();
        static RSTask* createReorientationTask();
        
    protected:
        rsToolRegistration* createReorientationToolRegistration();
        rsXSDExtension* createReorientationToolXSDExtension();
};

}}}} // namespace rstools::batch::plugins::reorientation

extern "C" {
    G_MODULE_EXPORT Plugin* rsGetPlugin(void);
}

#endif
