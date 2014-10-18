#include "smoothing.hpp"
#include "utils/rsstring.h"
#include "batch/util/rsunix.hpp"

using namespace rstools::batch::util;

namespace rstools {
namespace batch {
namespace plugins {
namespace smoothing {
namespace tool {
    
void Smoothing::_parseParams(int argc, char * argv[])
{   
    this->executionSuccessful = true;
}
    
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

bool Smoothing::isEverythingFine()
{
    return this->executionSuccessful;
}

rstools::batch::plugins::smoothing::task::Smoothing* Smoothing::getSmoothingTask()
{
    return (rstools::batch::plugins::smoothing::task::Smoothing*)this->getTask();
}

void Smoothing::_run()
{
    this->executionSuccessful = rsExecuteUnixCommand(this->getSmoothingTask()->getCmd());
}

rsUIInterface* Smoothing::createUI()
{    
    rsUIOption *o;
    rsUIInterface* interface = rsUINewInterface();
    interface->description   = rsString("Smoothing (FSL's susan or fslmaths)");
    
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

void Smoothing::printCallString(FILE *stream)
{
    int argc;
    char **argv = getCallString(&argc);

    fprintf(stream, "Tool:\n %s\n\nParams:\n", getTask()->getName());
    for ( int i=1; i<argc; i++ ) {
        fprintf(stream, "  %s\n", argv[i]);
    }
    
    fprintf(stream, "\n");
    
    fprintf(stream, "Cmd:\n%s\n", getSmoothingTask()->getCmd());
    fprintf(stream, "\n");
}

}}}}} // namespace rstools::batch::plugins::smoothing::tool
