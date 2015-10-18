#ifndef rstools_rsbatch_plugins_normalization_normalization_h
#define rstools_rsbatch_plugins_normalization_normalization_h

#include "rscommon.h"
#include "batch/util/plugin.hpp"
#include "tool/normalization.hpp"
#include "task/normalization.hpp"
#include "task/newnormalization.hpp"

using namespace rstools::batch::util;

namespace rstools {
namespace batch {
namespace plugins {
namespace normalization {

class Normalization : Plugin {

    public:
        Normalization();
        void  registerPlugin();
        const char* getName();
        const char* getCode();
        const char* getNewName();
        const char* getNewCode();
        const char* getVersion();

        static RSTool* createNormalizationTool();
        static RSTool* createNewNormalizationTool();
        static RSTask* createNormalizationTask();
        static RSTask* createNewNormalizationTask();
        
    protected:
        rsToolRegistration* createNormalizationToolRegistration();
        rsXSDExtension* createNormalizationToolXSDExtension();

        rsToolRegistration* createNewNormalizationToolRegistration();
        rsXSDExtension* createNewNormalizationToolXSDExtension();
};

}}}} // namespace rstools::batch::plugins::normalization

extern "C" {
    G_MODULE_EXPORT Plugin* rsGetPlugin(void);
}

#endif
