#include "reorientation.hpp"

using namespace rstools::batch::util;

namespace rstools {
namespace batch {
namespace plugins {
namespace reorientation {
namespace task {
   
Reorientation::Reorientation(const char* code, const char* name) : RSTask(code, name)
{}

char* Reorientation::getCmd() {
    
    rsArgument *input = this->getArgument("input");
    rsArgument *output = this->getArgument("output");
    rsArgument *orientation = this->getArgument("orientation");
    
    const char *afniPath = this->getJob()->getArgument("afniPath")->value;
    const char *orientationCmd = (orientation == NULL)
                                 ? "LPI"
                                 : orientation->value;
    
    return rsStringConcat(
        "rm -f ", output->value,
        "\n",
        afniPath, "/3daxialize", " -prefix ", output->value, " -orient ", orientationCmd, " ", input->value,
        NULL
    );
}

}}}}} // namespace rstools::batch::plugins::reorientation::task
