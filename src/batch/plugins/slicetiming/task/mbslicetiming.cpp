#include "mbslicetiming.hpp"

using namespace rstools::batch::util;

namespace rstools {
namespace batch {
namespace plugins {
namespace slicetiming {
namespace task {
   
MBSliceTiming::MBSliceTiming(const char* code, const char* name) : RSUnixTask(code, name)
{}

char* MBSliceTiming::getCmd() {
    
    const char *input        = this->getArgument("in")->value;
    const char *output       = this->getArgument("out")->value;
    const char *tcustom      = this->getArgument("tcustom")->value;
    rsArgument *meanArg      = this->getArgument("mean");
    rsArgument *directionArg = this->getArgument("direction");
    
    char *fslPath = this->getJob()->getArgument("fslPath")->value;
    
    const char *mean      = (meanArg == NULL)
                            ? NULL
                            : meanArg->value;
    
    const char *direction = (directionArg==NULL || !strcmp(directionArg->value, "z"))
                            ? "3"
                            : (!strcmp(directionArg->value, "x") ? "1" : "2");
    
    // prepare the call for the slicetimer    
    char *cmd = rsStringConcat(
        fslPath, "/slicetimer --in=", input, " --out=", output, " --tcustom=", tcustom, " --direction=", direction,
        NULL
    );
    
    
    // prepare the computation of the mean
    if ( mean != NULL ) {
        char *oldCmd = cmd;
        cmd = rsStringConcat(
            cmd,
            "\n",
            fslPath, "/fslmaths ", output, " -Tmean ", mean,
            NULL
        );
        rsFree(oldCmd);
    }
    
    return cmd;
}

}}}}} // namespace rstools::batch::plugins::slicetiming::task
