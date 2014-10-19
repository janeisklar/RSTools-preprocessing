#ifndef rstools_rsbatch_plugins_transformation_transformation_h
#define rstools_rsbatch_plugins_transformation_transformation_h

#include "rscommon.h"
#include "batch/util/plugin.hpp"
#include "tool/transformation.hpp"
#include "task/transformation.hpp"

using namespace rstools::batch::util;

namespace rstools {
namespace batch {
namespace plugins {
namespace transformation {

class Transformation : Plugin {

    public:
        Transformation();
        void  registerPlugin();
        const char* getName();
        const char* getCode();
        const char* getVersion();

        static RSTool* createTransformationTool();
        static RSTask* createTransformationTask();
        
    protected:
        rsToolRegistration* createTransformationToolRegistration();
        rsXSDExtension* createTransformationToolXSDExtension();
};

}}}} // namespace rstools::batch::plugins::transformation

extern "C" {
    G_MODULE_EXPORT Plugin* rsGetPlugin(void);
}

#endif
