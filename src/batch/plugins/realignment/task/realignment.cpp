#include <batch/util/rstask.hpp>
#include "realignment.hpp"

using namespace rstools::batch::util;

namespace rstools {
namespace batch {
namespace plugins {
namespace realignment {
namespace task {
   
Realignment::Realignment(const char* code, const char* name) : RSUnixTask(code, name)
{}

char* Realignment::getCmd(bool asExecuted) {
    
    rsArgument *input = this->getArgument("input");
    rsArgument *output = asExecuted ? this->getArgument("rsstream_output") : this->getArgument("output");
    rsArgument *finalOutput = this->getArgument("output");
    rsArgument *stages = this->getArgument("stages");
    rsArgument *mean = this->getArgument("mean");
    
    const char *fslPath = this->getJob()->getArgument("fslPath")->value;

    string cmd;

    // assemble mcflirt command
    cmd.append(fslPath);
    cmd.append("/mcflirt");
    cmd.append(" -in ").append(input->value);
    cmd.append(" -out ").append(output->value);
    if (stages == NULL) {
        cmd.append(" -stages 4");
    } else {
        cmd.append(" -stages ").append(stages->value);
    }

    // sinc_final interpolation has been disabled, as it takes too long and we interpolate it once more anyway
    //if (stages == NULL || strcmp(stages->value, "4") == 0) {
    //    cmd.append(" -sinc_final");
    //}

    cmd.append(" -mats");
    cmd.append(" -plots");
    cmd.append(" -meanvol");

    // if requested, also compute the mean
    if (mean != NULL && strlen(mean->value) > 0) {
        cmd.append("\n");
        cmd.append(fslPath);
        cmd.append("/fslmaths ").append(finalOutput->value).append(" -Tmean ").append(mean->value);
    }

    return rsString(cmd.c_str());
}

}}}}} // namespace rstools::batch::plugins::realignment::task
