#include "regressors.hpp"
#include "utils/rsstring.h"
#include "batch/util/rsunix.hpp"

using namespace rstools::batch::util;

namespace rstools {
namespace batch {
namespace plugins {
namespace regressors {
namespace tool {
    
void Regressors::_parseParams(int argc, char * argv[])
{   
    this->executionSuccessful = true;
}
    
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

bool Regressors::isEverythingFine()
{
    return this->executionSuccessful;
}

rstools::batch::plugins::regressors::task::Regressors* Regressors::getRegressorsTask()
{
    return (rstools::batch::plugins::regressors::task::Regressors*)this->getTask();
}

void Regressors::_run()
{
    this->executionSuccessful = rsExecuteUnixCommand(this->getRegressorsTask()->getCmd());
}

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

void Regressors::printCallString(FILE *stream)
{
    int argc;
    char **argv = getCallString(&argc);

    fprintf(stream, "Tool:\n %s\n\nParams:\n", getTask()->getName());
    for ( int i=1; i<argc; i++ ) {
        fprintf(stream, "  %s\n", argv[i]);
    }
    
    fprintf(stream, "\n");
    
    fprintf(stream, "Cmd:\n%s\n", getRegressorsTask()->getCmd());
    fprintf(stream, "\n");
}

}}}}} // namespace rstools::batch::plugins::regressors::tool
