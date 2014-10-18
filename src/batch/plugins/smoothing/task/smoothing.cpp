#include "smoothing.hpp"
#include <math.h>

using namespace rstools::batch::util;

namespace rstools {
namespace batch {
namespace plugins {
namespace smoothing {
namespace task {
   
Smoothing::Smoothing(const char* code, const char* name) : RSTask(code, name)
{}

char* Smoothing::getCmd() {
    
    // obtain parameters
    rsArgument *input = this->getArgument("input");
    rsArgument *output = this->getArgument("output");
    rsArgument *method = this->getArgument("method");
    rsArgument *kernelSize = this->getArgument("kernelSize");
    rsArgument *brightnessThreshold = this->getArgument("brightnessThreshold");
    
    const char *fslPath = this->getJob()->getArgument("fslPath")->value;

    const bool susan = (method == NULL)
                       ? false
                       : strcmp(method->value, "susan") == 0;
    
    const char *brightnessThresholdCmd = (brightnessThreshold == NULL)
                       ? "40"
                       : brightnessThreshold->value;
    
    // convert FWHM to HWHM
    const float kernelSizeFWHM = (kernelSize == NULL)
                                 ? 6.0
                                 : atof(kernelSize->value);
    
    const float kernelSizeHWHM = kernelSizeFWHM / (2.0*sqrt(2.0*log(2.0)));
    
    char *kernelSizeCmd = (char*)rsMalloc(sizeof(char)*9);
    sprintf(kernelSizeCmd, "%.5f", kernelSizeHWHM);
    
    // build unix command
    char *cmd;
    
    if ( susan ) {    
        cmd = rsStringConcat(
            "# compute brightness intensity threshold\n",
            "tmpfile=`mktemp 2>/dev/null || mktemp -t 'rstools-pps'`\n",
            fslPath, "/fslstats ", input->value, " -r > $tmpfile\n",
            "lowerBound=`cut -f 1 -d' ' $tmpfile`\n",
            "upperBound=`cut -f 2 -d' ' $tmpfile`\n",
            "rm -rf $tmpfile\n",
            "robustRange=$((($upperBound-$lowerBound)*", brightnessThresholdCmd, "/100))\n\n",
            "# run smoothing\n",
            fslPath, "/susan ", input->value, " $robustRange ", kernelSizeCmd, " 3 0 0 ", output->value,
            NULL
        );
    } else {
        cmd = rsStringConcat(
            fslPath, "/fslmaths ", input->value, " -s ", kernelSizeCmd, " ", output->value,
            NULL
        );
    }
    
    rsFree(kernelSizeCmd);
    
    return cmd;
}

}}}}} // namespace rstools::batch::plugins::smoothing::task
