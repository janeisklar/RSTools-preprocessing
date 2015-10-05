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

    if ( input == NULL ) {
        fprintf(stderr, "An input needs to be specified!\n");
        this->executionSuccessful = false;
    }
    
    if ( output == NULL ) {
        fprintf(stderr, "An output needs to be specified!\n");
        this->executionSuccessful = false;
    }

    if ( vdm == NULL ) {
        fprintf(stderr, "A voxe-displacement map needs to be specified!\n");
        this->executionSuccessful = false;
    }
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
    
    o = rsUINewOption();
    o->name                = rsString("vdm");
    o->shorthand           = 'v';
    o->type                = G_OPTION_ARG_FILENAME;
    o->cli_description     = rsString("The path to the voxel-displacement map. Please make sure it has the same orientation as the input image.");
    o->cli_arg_description = rsString("<volume>");
    rsUIAddOption(interface, o);
    
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

    // create stream
    return this->_createStream(streamName);
}

}}}}} // namespace rstools::batch::plugins::distcorrection::tool
