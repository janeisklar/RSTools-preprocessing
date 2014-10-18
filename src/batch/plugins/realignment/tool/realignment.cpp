#include "realignment.hpp"
#include "utils/rsstring.h"
#include "batch/util/rsunix.hpp"

using namespace rstools::batch::util;

namespace rstools {
namespace batch {
namespace plugins {
namespace realignment {
namespace tool {
    
void Realignment::_parseParams(int argc, char * argv[])
{   
    this->executionSuccessful = true;
}
    
void Realignment::_init()
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

void Realignment::destroy()
{}

bool Realignment::isEverythingFine()
{
    return this->executionSuccessful;
}

rstools::batch::plugins::realignment::task::Realignment* Realignment::getRealignmentTask()
{
    return (rstools::batch::plugins::realignment::task::Realignment*)this->getTask();
}

void Realignment::_run()
{
    this->executionSuccessful = rsExecuteUnixCommand(this->getRealignmentTask()->getCmd());
}

rsUIInterface* Realignment::createUI()
{    
    rsUIOption *o;
    rsUIInterface* interface = rsUINewInterface();
    interface->description   = rsString("Realignment (FSL's MCFLIRT)");
    
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
    o->name                = rsString("stages");
    o->shorthand           = 's';
    o->type                = G_OPTION_ARG_INT;
    o->cli_description     = rsString("Number of search levels. For more information refer to MCFLIRT.");
    o->cli_arg_description = rsString("<nstages>");
    o->defaultValue        = rsString("4");
    rsUIAddOption(interface, o);
    
    return interface;
}

void Realignment::printCallString(FILE *stream)
{
    int argc;
    char **argv = getCallString(&argc);

    fprintf(stream, "Tool:\n %s\n\nParams:\n", getTask()->getName());
    for ( int i=1; i<argc; i++ ) {
        fprintf(stream, "  %s\n", argv[i]);
    }
    
    fprintf(stream, "\n");
    
    fprintf(stream, "Cmd:\n%s\n", getRealignmentTask()->getCmd());
    fprintf(stream, "\n");
}

}}}}} // namespace rstools::batch::plugins::realignment::tool
