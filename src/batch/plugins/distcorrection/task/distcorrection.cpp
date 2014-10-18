#include "distcorrection.hpp"

using namespace rstools::batch::util;

namespace rstools {
namespace batch {
namespace plugins {
namespace distcorrection {
namespace task {
   
Distcorrection::Distcorrection(const char* code, const char* name) : RSTask(code, name)
{}

char* Distcorrection::getCmd() {
    
    rsArgument *input  = this->getArgument("input");
    rsArgument *output = this->getArgument("output");
    rsArgument *vdm    = this->getArgument("vdm");
    rsArgument *mean   = this->getArgument("mean");
    
    const char *fslPath = this->getJob()->getArgument("fslPath")->value;

    const char *meanCmd = (mean == NULL)
                         ? ""
                         : rsStringConcat(fslPath, "/fslmaths ", output->value, " -Tmean ", mean->value, NULL);
    
    return rsStringConcat(
        fslPath, "/fugue -i ", input->value, " --loadshift=", vdm->value, " -u ", output->value,
        "\n",
        meanCmd,
        NULL
    );
}

}}}}} // namespace rstools::batch::plugins::distcorrection::task
