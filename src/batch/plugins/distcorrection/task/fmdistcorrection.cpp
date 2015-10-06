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
    rsArgument *mean        = this->getArgument("mean");
    rsArgument *dwellTime   = this->getArgument("dwellTime");
    rsArgument *phaseEncDir = this->getArgument("phaseEncDir");
    
    const char *fslPath  = this->getJob()->getArgument("fslPath")->value;
    const char *dwellArg = (dwellTime == NULL)
                           ? rsString("")
                           : rsStringConcat(" --dwell=", dwellTime->value, NULL);

    const char *phaseEncDirArg = (phaseEncDir == NULL)
                                 ? rsString("")
                                 : rsStringConcat(" --unwarpdir=", phaseEncDir->value, NULL);

    if (mean == NULL) {
        return rsStringConcat(
            fslPath, "/fugue -i ", input->value, " --loadfmap=", fieldmap->value, dwellArg, phaseEncDirArg, " -u ", output->value, NULL
        );
    } else {
        return rsStringConcat(
            fslPath, "/fugue -i ", input->value, " --loadfmap=", fieldmap->value, dwellArg, phaseEncDirArg, " -u ", output->value,
            "\n",
            fslPath, "/fslmaths ", finalOutput->value, " -Tmean ", mean->value,
            NULL
        );
    }
}

}}}}} // namespace rstools::batch::plugins::fmdistcorrection::task
