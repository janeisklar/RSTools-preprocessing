#include "slicetiming.hpp"
#include "utils/rsstring.h"
#include "batch/util/rsunix.hpp"

using namespace rstools::batch::util;

namespace rstools {
namespace batch {
namespace plugins {
namespace slicetiming {
namespace tool {
    
void SliceTiming::_parseParams(int argc, char * argv[])
{   
    this->executionSuccessful = true;
}
    
void SliceTiming::_init()
{}

void SliceTiming::destroy()
{}

bool SliceTiming::isEverythingFine()
{
    return this->executionSuccessful;
}

rstools::batch::plugins::slicetiming::task::SliceTiming* SliceTiming::getSliceTimingTask()
{
    return (rstools::batch::plugins::slicetiming::task::SliceTiming*)this->getTask();
}

void SliceTiming::_run()
{
    this->executionSuccessful = rsExecuteUnixCommand(this->getSliceTimingTask()->getCmd());
}

rsUIInterface* SliceTiming::createUI()
{
    /*GOptionArgFunc cbAcquisitionDirection = (GOptionArgFunc)parseAcquisitionDirection;
    GOptionArgFunc cbSliceIndexing = (GOptionArgFunc)parseSliceIndexing;*/
    
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
    o->name                = rsString("direction");
    o->shorthand           = 'd';
    o->type                = G_OPTION_ARG_CALLBACK;
    o->cli_description     = rsString("direction of slice acquisition");
    o->cli_arg_description = rsString("<order>");
    o->defaultValue        = rsString("bottom-up");
    rsUIOptionValue allowedValues2[] = {
      {rsString("x"),  rsString("acquisition in x-direction")},
      {rsString("y"),  rsString("acquisition in y-direction")},
      {rsString("z"),  rsString("acquisition in z-direction")},
      NULL
    };
    rsUISetOptionValues(o, allowedValues2);
    rsUIAddOption(interface, o);
    
    o = rsUINewOption();
    o->name                = rsString("odd");
    o->shorthand           = 'o';
    o->cli_description     = rsString("use interleaved acquisition");
    rsUIAddOption(interface, o);
    
    return interface;
}

void SliceTiming::printCallString(FILE *stream)
{
    int argc;
    char **argv = getCallString(&argc);

    fprintf(stream, "Tool:\n %s\n\nParams:\n", getTask()->getName());
    for ( int i=1; i<argc; i++ ) {
        fprintf(stream, "  %s\n", argv[i]);
    }
    
    fprintf(stream, "\n");
    
    fprintf(stream, "Cmd:\n%s\n", getSliceTimingTask()->getCmd());
    fprintf(stream, "\n");
}

}}}}} // namespace rstools::batch::plugins::slicetiming::tool
