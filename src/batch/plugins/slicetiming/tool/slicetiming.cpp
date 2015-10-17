#include <nifti/headerinfo.h>
#include "slicetiming.hpp"
#include "utils/rsstring.h"
#include "batch/util/rsunix.hpp"

using namespace rstools::batch::util;

namespace rstools {
namespace batch {
namespace plugins {
namespace slicetiming {
namespace tool {
    
void SliceTiming::_init()
{
    rsArgument *input = this->getTask()->getArgument("in");
    rsArgument *output = this->getTask()->getArgument("out");
    
    if ( input == NULL ) {
        fprintf(stderr, "An input needs to be specified!\n");
        this->executionSuccessful = false;
    }
    
    if ( output == NULL ) {
        fprintf(stderr, "An output needs to be specified!\n");
        this->executionSuccessful = false;
    }
    
    if ( !this->multibandActive ) {
        rsArgument *repeat = this->getTask()->getArgument("repeat");
        
        if ( repeat == NULL ) {
            fprintf(stderr, "The TR needs to be specified!\n");
            this->executionSuccessful = false;
        }
    }
}

void SliceTiming::destroy()
{}

rsUIInterface* SliceTiming::createUI()
{    
    rsUIOption *o;
    rsUIInterface* interface = rsUINewInterface();
    interface->description   = rsString("Slice Timing (FSL's slicetimer)");
    
    o = rsUINewOption();
    o->name                = rsString("in");
    o->shorthand           = 'i';
    o->type                = G_OPTION_ARG_FILENAME;
    o->cli_description     = rsString("the 4D volume to be slice-timed");
    o->cli_arg_description = rsString("<volume>");
    rsUIAddOption(interface, o);
    
    o = rsUINewOption();
    o->name                = rsString("out");
    o->shorthand           = 'o';
    o->type                = G_OPTION_ARG_FILENAME;
    o->cli_description     = rsString("path to the resulting slice-timed 4D volume");
    o->cli_arg_description = rsString("<volume>");
    rsUIAddOption(interface, o);
    
    o = rsUINewOption();
    o->name                = rsString("mean");
    o->shorthand           = 'm';
    o->type                = G_OPTION_ARG_FILENAME;
    o->cli_description     = rsString("if specified, the mean of the slice-timed volume will be saved as well");
    o->cli_arg_description = rsString("<volume>");
    rsUIAddOption(interface, o);
    
    
    if ( multibandActive ) { 
        o = rsUINewOption();
        o->name                = rsString("tcustom");
        o->shorthand           = 't';
        o->type                = G_OPTION_ARG_FILENAME;
        o->cli_description     = rsString("filename of single-column slice timings, in fractions of TR, +ve values shift slices forwards in time. This file can be omitted if the nifti header contains the slice acquisition times and TR (if not specified, the correction to the middle of the acquistion time is automatically computed using the data form the header).");
        o->cli_arg_description = rsString("<txt-file>");
        rsUIAddOption(interface, o);
    } else {
        o = rsUINewOption();
        o->name                = rsString("sliceIndexing");
        o->shorthand           = 'r';
        o->type                = G_OPTION_ARG_CALLBACK;
        o->cli_description     = rsString("order of slice-indexing");
        o->cli_arg_description = rsString("<order>");
        o->defaultValue        = rsString("bottom-up");
        rsUIOptionValue allowedValues[] = {
          {rsString("bottom-up"),  rsString("slices were acquired bottom-up")},
          {rsString("top-down"),  rsString("slices were acquired top-down")},
          NULL
        };
        rsUISetOptionValues(o, allowedValues);
        rsUIAddOption(interface, o);
       
        o = rsUINewOption();
        o->name                = rsString("repeat");
        o->shorthand           = 'r';
        o->type                = G_OPTION_ARG_DOUBLE;
        o->cli_description     = rsString("specify TR of data");
        o->cli_arg_description = rsString("<rate in s>");
        rsUIAddOption(interface, o);
        
        o = rsUINewOption();
        o->name                = rsString("ocustom");
        o->shorthand           = 'c';
        o->type                = G_OPTION_ARG_FILENAME;
        o->cli_description     = rsString("filename of single-column custom interleave order file (first slice is referred to as 1 not 0)");
        o->cli_arg_description = rsString("<*.txt>");
        rsUIAddOption(interface, o);
    }
    
    o = rsUINewOption();
    o->name                = rsString("direction");
    o->shorthand           = 'd';
    o->type                = G_OPTION_ARG_CALLBACK;
    o->cli_description     = rsString("direction of slice acquisition");
    o->cli_arg_description = rsString("<order>");
    o->defaultValue        = rsString("z");
    rsUIOptionValue allowedValues2[] = {
      {rsString("x"),  rsString("acquisition in x-direction")},
      {rsString("y"),  rsString("acquisition in y-direction")},
      {rsString("z"),  rsString("acquisition in z-direction")},
      NULL
    };
    rsUISetOptionValues(o, allowedValues2);
    rsUIAddOption(interface, o);
    
    if ( ! multibandActive ) { 
        o = rsUINewOption();
        o->name                = rsString("odd");
        o->shorthand           = 'o';
        o->cli_description     = rsString("use interleaved acquisition");
        rsUIAddOption(interface, o);
    }
    
    return interface;
}

void SliceTiming::setMultibandActive(bool mbActive)
{
    this->multibandActive = mbActive;
}

bool SliceTiming::_prepareStream()
{
    // assemble temporary stream path
    streamName = rsStringConcat(tmpDirPath, "/stream.nii", NULL);

    // add stream to list of job arguments
    rsArgument *arg = (rsArgument*)malloc(sizeof(rsArgument));
    arg->key = rsString("rsstream_out");
    arg->value = rsString(streamName);
    getUnixTask()->addArgument(arg);

    // set the target path of the stream
    streamTarget = rsString(getUnixTask()->getArgument("out")->value);

    // read in header information of the input nifti
    inputNifti = nifti_image_read(getUnixTask()->getArgument("in")->value, false);

    // read out slice timings (if present);
    rsNiftiFile* input = rsOpenNiftiFile(getUnixTask()->getArgument("in")->value, RSNIFTI_OPEN_NONE);
    rsNiftiExtendedHeaderInformation* info;
    info = rsNiftiFindExtendedHeaderInformation(input->fslio->niftiptr);

    if (info != NULL && !isnan(info->MosaicRefAcqTimes[0])) {
        getUnixTask()->setInputNiftiHeaderInformation(info);
    }

    // close nifti
    rsCloseNiftiFile(input, FALSE);
    rsFreeNiftiFile(input);

    // create stream
    return this->_createStream(streamName);
}

}}}}} // namespace rstools::batch::plugins::slicetiming::tool
