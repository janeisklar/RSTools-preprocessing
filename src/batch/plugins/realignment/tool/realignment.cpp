#include "realignment.hpp"
#include "utils/rsstring.h"

using namespace rstools::batch::util;

namespace rstools {
namespace batch {
namespace plugins {
namespace realignment {
namespace tool {
    
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

}}}}} // namespace rstools::batch::plugins::realignment::tool
