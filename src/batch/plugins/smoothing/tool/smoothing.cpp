#include "smoothing.hpp"
#include "utils/rsstring.h"

using namespace rstools::batch::util;

namespace rstools {
namespace batch {
namespace plugins {
namespace smoothing {
namespace tool {

void Smoothing::_init()
{
    rsArgument *input = this->getTask()->getArgument("input");
    rsArgument *output = this->getTask()->getArgument("output");
    
    if ( input == NULL ) {
        fprintf(stderr, "An input needs to be specified!\n");
        this->executionSuccessful = false;
    }
    
    if ( output == NULL ) {
        fprintf(stderr, "An output needs to be specified!\n");
        this->executionSuccessful = false;
    }
}

void Smoothing::destroy()
{}

rsUIInterface* Smoothing::createUI()
{    
    rsUIOption *o;
    rsUIInterface* interface = rsUINewInterface();
    interface->description   = rsString("Smoothing (FSL's susan/fslmaths)");
    
    o = rsUINewOption();
    o->name                = rsString("input");
    o->shorthand           = 'i';
    o->type                = G_OPTION_ARG_FILENAME;
    o->cli_description     = rsString("path to the dataset which is to be de-spiked");
    o->cli_arg_description = rsString("<volume>");
    rsUIAddOption(interface, o);
    
    o = rsUINewOption();
    o->name                = rsString("output");
    o->shorthand           = 'o';
    o->type                = G_OPTION_ARG_FILENAME;
    o->cli_description     = rsString("path of the resulting de-spiked dataset");
    o->cli_arg_description = rsString("<volume>");
    rsUIAddOption(interface, o);
    
    o = rsUINewOption();
    o->name                = rsString("method");
    o->shorthand           = 'm';
    o->type                = G_OPTION_ARG_CALLBACK;
    o->cli_description     = rsString("The smoothing method used. While fslmaths considers all surrounding voxels in the gaussian kernel for smoothing, the susan method limits itself to voxels with a similar intensity (see the brightnessThreshold parameter).");
    o->cli_arg_description = rsString("<method>");
    o->defaultValue        = rsString("fslmaths");
    rsUIOptionValue allowedValues2[] = {
      {rsString("fslmaths"), rsString("gaussian smoothing based on fslmaths")},
      {rsString("susan"), rsString("gaussian smoothing based on susan")},
      NULL
    };
    rsUISetOptionValues(o, allowedValues2);
    rsUIAddOption(interface, o);
    
    o = rsUINewOption();
    o->name                = rsString("kernelSize");
    o->shorthand           = 'k';
    o->type                = G_OPTION_ARG_DOUBLE;
    o->cli_description     = rsString("The size of the gaussian kernel in mm (FWHM). Conversion to HWHM (as commonly used throughout FSL) is done automatically.");
    o->cli_arg_description = rsString("<corder>");
    o->defaultValue        = rsString("6.0");
    rsUIAddOption(interface, o);
    
    o = rsUINewOption();
    o->name                = rsString("brightnessThreshold");
    o->shorthand           = 'b';
    o->type                = G_OPTION_ARG_DOUBLE;
    o->cli_description     = rsString("Percentage of the robust range that will be used as a brightness threshold. Only voxels with an intensity difference of at most <n>% to the voxel in question will then be considered for smoothing. This option only applies to the susan smoothing method.");
    o->cli_arg_description = rsString("<n>");
    o->defaultValue        = rsString("40");
    rsUIAddOption(interface, o);
    
    return interface;
}

bool Smoothing::_prepareStream()
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

}}}}} // namespace rstools::batch::plugins::smoothing::tool
