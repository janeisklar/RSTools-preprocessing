#include "bfcorrection.hpp"

using namespace rstools::batch::util;

namespace rstools {
namespace batch {
namespace plugins {
namespace bfcorrection {
namespace task {
   
BFCorrection::BFCorrection(const char* code, const char* name) : RSTask(code, name)
{}

char* BFCorrection::getCmd() {
    
    rsArgument *input = this->getArgument("input");
    rsArgument *input2 = this->getArgument("secondaryInput");
    rsArgument *output = this->getArgument("output");
    rsArgument *bfield = this->getArgument("bfield");
    rsArgument *shrinkfactor = this->getArgument("shrinkfactor");
    
    const char *antsPath = this->getJob()->getArgument("ANTSPATH")->value;
    const char *fslPath = this->getJob()->getArgument("fslPath")->value;
    const char *shrinkCmd = (shrinkfactor==NULL) ? "2" : shrinkfactor->value;
    const char *bfieldCmd = (bfield==NULL) ? "$tmpdir/bfield.nii" : bfield->value;
    
    return rsStringConcat(
        "tmpdir=`mktemp -d 2>/dev/null || mktemp -d -t 'rstools-pps'`"
        "\n",
        antsPath, "N4BiasFieldCorrection -i ", input2->value, " -d 3 -s ", shrinkCmd, " -o [$tmpdir/corrected.nii,", bfieldCmd, "]",
        "\n",
        fslPath, "/fslmaths ", input->value, " -div ", bfieldCmd, " ", output->value,
        "\n",
        "rm -rf $tmpdir",
        NULL
    );
}

}}}}} // namespace rstools::batch::plugins::bfcorrection::task
