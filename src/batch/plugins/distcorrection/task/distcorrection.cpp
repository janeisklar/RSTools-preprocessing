#include "distcorrection.hpp"

using namespace rstools::batch::util;

namespace rstools {
namespace batch {
namespace plugins {
namespace distcorrection {
namespace task {
   
Distcorrection::Distcorrection(const char* code, const char* name) : RSUnixTask(code, name)
{}

char* Distcorrection::getCmd(bool asExecuted) {
    
    rsArgument *input       = this->getArgument("input");
    rsArgument *output      = asExecuted ? this->getArgument("rsstream_output") : this->getArgument("output");
    rsArgument *finalOutput = this->getArgument("output");
    rsArgument *vdm         = this->getArgument("vdm");
    rsArgument *mean        = this->getArgument("mean");
    
    const char *fslPath = this->getJob()->getArgument("fslPath")->value;

    if (mean == NULL) {
        return rsStringConcat(
            fslPath, "/fugue -i ", input->value, " --loadshift=", vdm->value, " -u ", output->value, NULL
        );
    } else {
        return rsStringConcat(
            fslPath, "/fugue -i ", input->value, " --loadshift=", vdm->value, " -u ", output->value,
            "\n",
            fslPath, "/fslmaths ", finalOutput->value, " -Tmean ", mean->value,
            NULL
        );
    }
}

}}}}} // namespace rstools::batch::plugins::distcorrection::task
