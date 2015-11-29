#include <nifti/rsniftiutils.h>
#include <externals/fslio/fslio.h>
#include <nifti/headerinfo.h>
#include "distcorrection.hpp"
#include "utils/rsstring.h"

using namespace rstools::batch::util;

namespace rstools {
namespace batch {
namespace plugins {
namespace distcorrection {
namespace tool {
    
void Distcorrection::_init()
{
    rsArgument *input = this->getTask()->getArgument("input");
    rsArgument *output = this->getTask()->getArgument("output");
    rsArgument *vdm = this->getTask()->getArgument("vdm");
    rsArgument *fieldmap = this->getTask()->getArgument("fieldmap");

    if ( input == NULL ) {
        fprintf(stderr, "An input needs to be specified!\n");
        this->executionSuccessful = false;
    }
    
    if ( output == NULL ) {
        fprintf(stderr, "An output needs to be specified!\n");
        this->executionSuccessful = false;
    }

    if ( mode == SHIFTMAP && vdm == NULL ) {
        fprintf(stderr, "A voxe-displacement map needs to be specified!\n");
        this->executionSuccessful = false;
    } else if (mode == FIELDMAP && fieldmap == NULL) {
        fprintf(stderr, "A fieldmap needs to be specified!\n");
        this->executionSuccessful = false;
    }
}

void Distcorrection::setMode(DistorionCorrectionMode mode)
{
    this->mode = mode;
}

void Distcorrection::destroy()
{}

rsUIInterface* Distcorrection::createUI()
{    
    rsUIOption *o;
    rsUIInterface* interface = rsUINewInterface();
    interface->description   = rsString("Distortion Correction (FSL's fugue)");
    
    o = rsUINewOption();
    o->name                = rsString("input");
    o->shorthand           = 'i';
    o->type                = G_OPTION_ARG_FILENAME;
    o->cli_description     = rsString("The path to the dataset which is to be unwarped.");
    o->cli_arg_description = rsString("<volume>");
    rsUIAddOption(interface, o);
    
    o = rsUINewOption();
    o->name                = rsString("output");
    o->shorthand           = 'o';
    o->type                = G_OPTION_ARG_FILENAME;
    o->cli_description     = rsString("The path of the resulting unwarped dataset.");
    o->cli_arg_description = rsString("<volume>");
    rsUIAddOption(interface, o);

    if (mode == SHIFTMAP) {
        o = rsUINewOption();
        o->name = rsString("vdm");
        o->shorthand = 'v';
        o->type = G_OPTION_ARG_FILENAME;
        o->cli_description = rsString("The path to the voxel-displacement map. Please make sure it has the same orientation as the input image.");
        o->cli_arg_description = rsString("<volume>");
        rsUIAddOption(interface, o);
    } else if (mode == FIELDMAP) {
        o = rsUINewOption();
        o->name = rsString("fieldmap");
        o->shorthand = 'f';
        o->type = G_OPTION_ARG_FILENAME;
        o->cli_description = rsString("The path to the fieldmap");
        o->cli_arg_description = rsString("<volume>");
        rsUIAddOption(interface, o);

        o = rsUINewOption();
        o->name = rsString("vdm");
        o->shorthand = 'v';
        o->type = G_OPTION_ARG_FILENAME;
        o->cli_description = rsString("The path to the resulting voxel-shift map. Fugue will create this file based on the given input and fieldmap.");
        o->cli_arg_description = rsString("<volume>");
        rsUIAddOption(interface, o);
    }

    o = rsUINewOption();
    o->name                = rsString("mean");
    o->shorthand           = 'm';
    o->type                = G_OPTION_ARG_FILENAME;
    o->cli_description     = rsString("If supplied, the mean of the unwarped 4D volume is computed and saved at the given path.");
    o->cli_arg_description = rsString("<volume>");
    rsUIAddOption(interface, o);
    
    return interface;
}

bool Distcorrection::_prepareStream()
{
    // assemble temporary stream path
    streamName = rsStringConcat(tmpDirPath, "/stream.nii", NULL);

    // add stream to list of job arguments
    rsArgument *arg = (rsArgument*)malloc(sizeof(rsArgument));
    arg->key = rsString("rsstream_output");
    arg->value = rsString(streamName);
    getUnixTask()->addArgument(arg);

    // set the target path of the stream
    streamTarget = rsString(getUnixTask()->getArgument("output")->value);

    // read in header information of the input nifti
    inputNifti = nifti_image_read(getUnixTask()->getArgument("input")->value, false);

    // read out dwell time (if present);
    rsNiftiFile* input = rsOpenNiftiFile(getUnixTask()->getArgument("input")->value, RSNIFTI_OPEN_NONE);
    rsNiftiExtendedHeaderInformation* info;
    info = rsNiftiFindExtendedHeaderInformation(input->fslio->niftiptr);

    if (info != NULL && !isnan(info->DwellTime)) {
        rsArgument *arg = (rsArgument*)malloc(sizeof(rsArgument));
        char *dwellTime = (char*)rsMalloc(sizeof(char)*30);
        sprintf(dwellTime, "%.10f", info->DwellTime);
        arg->key = rsString("dwellTime");
        arg->value = dwellTime;
        getUnixTask()->addArgument(arg);
    }

    if (info != NULL && info->PhaseEncodingDirection != NULL && strlen(&info->PhaseEncodingDirection[0]) == 2) {
        rsArgument *arg = (rsArgument*)malloc(sizeof(rsArgument));
        char *phaseEncDir = (char*)rsMalloc(sizeof(char)*3);
        sprintf(phaseEncDir, "%s", info->PhaseEncodingDirection);
        arg->key = rsString("phaseEncDir");
        arg->value = rsString(&info->PhaseEncodingDirection[0]);
        // fsl expects the format to be either y- or just y (for y+)
        if (arg->value[1]=='+') {
            arg->value[1] = '\0';
        }
        getUnixTask()->addArgument(arg);
    }

    rsCloseNiftiFile(input, FALSE);
    rsFreeNiftiFile(input);

    // create stream
    return this->_createStream(streamName);
}

}}}}} // namespace rstools::batch::plugins::distcorrection::tool
