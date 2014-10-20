#include "regressors.hpp"
#include "utils/rsstring.h"

using namespace rstools::batch::util;

namespace rstools {
namespace batch {
namespace plugins {
namespace regressors {
namespace tool {
    
void Regressors::_init()
{
    rsArgument *input = this->getTask()->getArgument("input");
    rsArgument *output = this->getTask()->getArgument("output");
    
    if ( input == NULL ) {
        fprintf(stderr, "Input files need to be specified!\n");
        this->executionSuccessful = false;
    }
    
    if ( output == NULL ) {
        fprintf(stderr, "An output needs to be specified!\n");
        this->executionSuccessful = false;
    }
}

void Regressors::destroy()
{}

rsUIInterface* Regressors::createUI()
{    
    rsUIOption *o;
    rsUIInterface* interface = rsUINewInterface();
    interface->description   = rsString("Merge regressor files with the regressors in the columns and the timecourse in the rows into one file");
    
    o = rsUINewOption();
    o->name                = rsString("input");
    o->shorthand           = 'i';
    o->type                = G_OPTION_ARG_STRING;
    o->nLines              = 5;
    o->cli_description     = rsString("specify paths to files whose columns are to be merged (one on each line)");
    o->cli_arg_description = rsString("<volume>");
    rsUIAddOption(interface, o);
    
    o = rsUINewOption();
    o->name                = rsString("output");
    o->shorthand           = 'o';
    o->type                = G_OPTION_ARG_FILENAME;
    o->cli_description     = rsString("path of the resulting de-spiked dataset");
    o->cli_arg_description = rsString("<volume>");
    rsUIAddOption(interface, o);
   
    return interface;
}

}}}}} // namespace rstools::batch::plugins::regressors::tool
