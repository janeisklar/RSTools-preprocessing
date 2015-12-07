#include <batch/util/rstask.hpp>
#include <nifti/headerinfo.h>
#include "mbslicetiming.hpp"

using namespace rstools::batch::util;

namespace rstools {
namespace batch {
namespace plugins {
namespace slicetiming {
namespace task {
   
MBSliceTiming::MBSliceTiming(const char* code, const char* name) : RSUnixTask(code, name)
{}

char* MBSliceTiming::getCmd(bool asExecuted) {
    
    const char *input        = this->getArgument("in")->value;
    const char *output       = asExecuted ? this->getArgument("rsstream_out")->value : this->getArgument("out")->value;
    const char *finalOutput  = this->getArgument("out")->value;
    char *tcustom            = this->getArgument("tcustom") == NULL ? rsString("") : this->getArgument("tcustom")->value;
    rsArgument *meanArg      = this->getArgument("mean");
    rsArgument *directionArg = this->getArgument("direction");
    
    char *fslPath = this->getJob()->getArgument("fslPath")->value;
    
    const char *mean      = (meanArg == NULL)
                            ? NULL
                            : meanArg->value;
    
    const char *direction = (directionArg==NULL || !strcmp(directionArg->value, "z"))
                            ? "3"
                            : (!strcmp(directionArg->value, "x") ? "1" : "2");

    char *cmd = rsString(""); // init with empty command
    char *oldCmd;

    // check if we need to compute the slice timing correction ourselves
    bool timingInfoSpecififed = tcustom != NULL && strlen(tcustom) > 0;
    bool hasTimingInfo = asExecuted && hasInputNiftiHeaderInformation() && !isnan(getInputNiftiHeaderInformation()->MosaicRefAcqTimes[0]);
    if (!timingInfoSpecififed && hasTimingInfo) {
        oldCmd = cmd;

        rsNiftiExtendedHeaderInformation *info = getInputNiftiHeaderInformation();
        const double TR = (double)atoi(info->RepetitionTime);
        const size_t nSliceTimings = sizeof(info->MosaicRefAcqTimes)/sizeof(double);
        char *strbuffer = (char*)rsMalloc(sizeof(char)*12*nSliceTimings);
        char *timingCorrections = strbuffer;

        for (short i=0; i<nSliceTimings && !isnan(info->MosaicRefAcqTimes[i]); i++) {
            if (i>0) {
                strbuffer += sprintf(strbuffer, ",");
            }
            const double timingCorrectionInTR = ((TR/2) - info->MosaicRefAcqTimes[i]) / TR;
            strbuffer += sprintf(strbuffer, "%g", timingCorrectionInTR);
        }

        rsFree(tcustom);
        tcustom = rsStringConcat(getTempDirectoryPath(), "/mb_timing_correction.txt", NULL);
        cmd = rsStringConcat("echo \"", timingCorrections, "\" | tr -s ',' '\\n' > ", tcustom, "\n", NULL);
        rsFree(oldCmd);
        rsFree(timingCorrections);
    } else if (!timingInfoSpecififed && !asExecuted) {
        // we're not actually executing just yet, so simply show how we would extract the data if we were to run it
        // (we can't read out the slice timing info from the header as the file might not yet exist)
        oldCmd = cmd;
        cmd = rsStringConcat("$(rsinfo -i ", input, " -k MosaicRefAcqTimes) > tcustom.txt\n", NULL);
        rsFree(tcustom);
        rsFree(oldCmd);
        tcustom = rsString("tcustom.txt");
    }

    // prepare the call for the slicetimer
    oldCmd = cmd;
    cmd = rsStringConcat(
        cmd,
        fslPath, "/slicetimer --in=", input, " --out=", output, " --tcustom=", tcustom, " --direction=", direction,
        NULL
    );
    rsFree(oldCmd);
    
    
    // prepare the computation of the mean
    if ( mean != NULL ) {
        oldCmd = cmd;
        cmd = rsStringConcat(
            cmd,
            "\n",
            fslPath, "/fslmaths ", finalOutput, " -Tmean ", mean,
            NULL
        );
        rsFree(oldCmd);
    }
    
    return cmd;
}

}}}}} // namespace rstools::batch::plugins::slicetiming::task
