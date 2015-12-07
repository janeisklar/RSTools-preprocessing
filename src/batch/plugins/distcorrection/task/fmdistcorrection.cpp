#include <batch/util/rstask.hpp>
#include "fmdistcorrection.hpp"

using namespace rstools::batch::util;

namespace rstools {
namespace batch {
namespace plugins {
namespace distcorrection {
namespace task {

FMDistcorrection::FMDistcorrection(const char* code, const char* name) : RSUnixTask(code, name)
{}

char* FMDistcorrection::getCmd(bool asExecuted) {
    
    rsArgument *input       = this->getArgument("input");
    rsArgument *output      = asExecuted ? this->getArgument("rsstream_output") : this->getArgument("output");
    rsArgument *finalOutput = this->getArgument("output");
    rsArgument *fieldmap    = this->getArgument("fieldmap");
    rsArgument *vdm         = this->getArgument("vdm");
    rsArgument *mean        = this->getArgument("mean");
    rsArgument *dwellTime   = this->getArgument("dwellTime");
    rsArgument *phaseEncDir = this->getArgument("phaseEncDir");
    
    const char *fslPath  = this->getJob()->getArgument("fslPath")->value;
    string cmd;

    // assemble fugue command
    cmd.append(fslPath);
    cmd.append("/fugue");
    cmd.append(" -i ").append(input->value);
    cmd.append(" --loadfmap=").append(fieldmap->value);
    if (dwellTime != NULL) {
        // if we have a dwell time add it
        cmd.append(" --dwell=").append(dwellTime->value);
    } else if (!asExecuted) {
        // if we're only displaying the command and didn't read out the dwell time yet, show how it's acquired instead
        cmd.append(" --dwell=$(rsinfo -i ").append(input->value).append(" -k DwellTime)");
    }
    if (phaseEncDir != NULL) {
        // if we have a dwell time add it
        cmd.append(" --unwarpdir=").append(phaseEncDir->value);
    } else if (!asExecuted) {
        // if we're only displaying the command and didn't read out the phase encoding direction yet, show how it's acquired instead
        cmd.append(" --unwarpdir=$(rsinfo -i ").append(input->value).append(" -k PhaseEncodingDirection)");
    }
    if (vdm != NULL) {
        cmd.append(" --saveshift=").append(vdm->value);
        cmd.append(" --unmaskshift");
    }
    cmd.append(" -u ").append(output->value);

    // if requested, also compute the mean
    if (mean!= NULL) {
        cmd.append("\n");
        cmd.append(fslPath);
        cmd.append("/fslmaths ").append(finalOutput->value).append(" -Tmean ").append(mean->value);
    }

    return rsString(cmd.c_str());
}

}}}}} // namespace rstools::batch::plugins::fmdistcorrection::task
