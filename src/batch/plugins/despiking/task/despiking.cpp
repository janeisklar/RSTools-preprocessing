#include "despiking.hpp"

using namespace rstools::batch::util;

namespace rstools {
namespace batch {
namespace plugins {
namespace despiking {
namespace task {
   
Despiking::Despiking(const char* code, const char* name) : RSUnixTask(code, name)
{}

char* Despiking::getCmd(bool asExecuted) {
    
    rsArgument *input = this->getArgument("input");
    rsArgument *output = asExecuted ? this->getArgument("rsstream_output") : this->getArgument("output");
    rsArgument *finalOutput = this->getArgument("output");
    rsArgument *corder = this->getArgument("corder");
    rsArgument *methodNew = this->getArgument("NEW");
    
    const char *afniPath = this->getJob()->getArgument("afniPath")->value;
    const char *corderCmd = (corder == NULL)
                            ? ""
                            : rsStringConcat(" -corder ", corder->value, NULL);
    const char *newCmd = (methodNew == NULL)
                         ? ""
                         : " -NEW";
    
    return rsStringConcat(
        "rm -f ", finalOutput->value,
        "\n",
        afniPath, "/3dDespike", " -prefix ", output->value, corderCmd, newCmd, " -nomask", " -q ", input->value,
        NULL
    );
}

}}}}} // namespace rstools::batch::plugins::despiking::task
