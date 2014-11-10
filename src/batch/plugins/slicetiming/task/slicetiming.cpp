#include "slicetiming.hpp"

using namespace rstools::batch::util;

namespace rstools {
namespace batch {
namespace plugins {
namespace slicetiming {
namespace task {
   
SliceTiming::SliceTiming(const char* code, const char* name) : RSUnixTask(code, name)
{}

char* SliceTiming::getCmd() {

    const char *input            = this->getArgument("in")->value;
    const char *output           = this->getArgument("out")->value;
    rsArgument *meanArg          = this->getArgument("mean");
    rsArgument *directionArg     = this->getArgument("direction");
    rsArgument *repeatArg        = this->getArgument("repeat");
    rsArgument *sliceIndexingArg = this->getArgument("sliceIndexing");
    rsArgument *oddArg           = this->getArgument("odd");
    rsArgument *ocustomArg       = this->getArgument("ocustom");

    char *fslPath = this->getJob()->getArgument("fslPath")->value;

    const char *mean             = (meanArg == NULL)
                                   ? NULL
                                   : meanArg->value;
                                 
    const char *direction        = (directionArg==NULL || !strcmp(directionArg->value, "z"))
                                   ? "3"
                                   : (!strcmp(directionArg->value, "x") ? "1" : "2");
                                 
    const char *repeat           = (repeatArg==NULL)
                                   ? "3"
                                   : repeatArg->value;
                                 
    const char *oddCmd           = (oddArg==NULL)
                                   ? ""
                                   : " --odd";
    
    const char *sliceIndexingCmd = (sliceIndexingArg==NULL || !strcmp(sliceIndexingArg->value, "bottom-up"))
                                   ? ""
                                   : " --down";
    
    const char *ocustomCmd       = (ocustomArg==NULL || !strcmp(ocustomArg->value, ""))
                                   ? ""
                                   : rsStringConcat(" --ocustom=", ocustomArg->value, NULL);

    // prepare the call for the slicetimer    
    char *cmd = rsStringConcat(
        fslPath, "/slicetimer --in=", input, " --out=", output, " --repeat=", repeat, " --direction=", direction, oddCmd, sliceIndexingCmd, ocustomCmd,
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
