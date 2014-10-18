#include "bfcorrection.hpp"
#include "utils/rsstring.h"
#include "batch/util/rsunix.hpp"

using namespace rstools::batch::util;

namespace rstools {
namespace batch {
namespace plugins {
namespace bfcorrection {
namespace tool {
    
void BFCorrection::_parseParams(int argc, char * argv[])
{   
    this->executionSuccessful = true;
}
    
void BFCorrection::_init()
{
    rsArgument *input = this->getTask()->getArgument("input");
    rsArgument *input2 = this->getTask()->getArgument("secondaryInput");
    rsArgument *output = this->getTask()->getArgument("output");
    
    if ( input == NULL ) {
        fprintf(stderr, "An input needs to be specified!\n");
        this->executionSuccessful = false;
    }
    
    if ( output == NULL ) {
        fprintf(stderr, "An output needs to be specified!\n");
        this->executionSuccessful = false;
    }
    
    if ( input2 == NULL ) {
        fprintf(stderr, "A secondary input needs to be specified!\n");
        this->executionSuccessful = false;
    }
}

void BFCorrection::destroy()
{}

bool BFCorrection::isEverythingFine()
{
    return this->executionSuccessful;
}

rstools::batch::plugins::bfcorrection::task::BFCorrection* BFCorrection::getBFCorrectionTask()
{
    return (rstools::batch::plugins::bfcorrection::task::BFCorrection*)this->getTask();
}

void BFCorrection::_run()
{
    this->executionSuccessful = rsExecuteUnixCommand(this->getBFCorrectionTask()->getCmd());
}

rsUIInterface* BFCorrection::createUI()
{    
    rsUIOption *o;
    rsUIInterface* interface = rsUINewInterface();
    interface->description   = rsString("Bias Field Correction (ANTs' N4BiasFieldCorrection)");
    
    o = rsUINewOption();
    o->name                = rsString("input");
    o->shorthand           = 'i';
    o->type                = G_OPTION_ARG_FILENAME;
    o->cli_description     = rsString("path to the 4D-dataset which is to be bias-field corrected");
    o->cli_arg_description = rsString("<volume>");
    rsUIAddOption(interface, o);

    o = rsUINewOption();
    o->name                = rsString("secondaryInput");
    o->shorthand           = 'j';
    o->type                = G_OPTION_ARG_FILENAME;
    o->cli_description     = rsString("path to a 3D-dataset (such as the mean of the first input) that is used for the estimation of the bias-field");
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
    o->name                = rsString("bfield");
    o->shorthand           = 'b';
    o->type                = G_OPTION_ARG_FILENAME;
    o->cli_description     = rsString("optional path where the bias-field may be stored");
    o->cli_arg_description = rsString("<volume>");
    rsUIAddOption(interface, o);
    
    o = rsUINewOption();
    o->name                = rsString("shrinkfactor");
    o->shorthand           = 's';
    o->type                = G_OPTION_ARG_INT;
    o->group               = RS_UI_GROUP_EXTENDED;
    o->cli_description     = rsString("Running N4 on large images can be time consuming. To lessen computation time, the input image can be resampled. The shrink factor, specified as a single integer, describes this resampling. Shrink factors <= 4 are commonly used");
    o->defaultValue        = rsString("2");
    rsUIAddOption(interface, o);
    
    return interface;
}

void BFCorrection::printCallString(FILE *stream)
{
    int argc;
    char **argv = getCallString(&argc);

    fprintf(stream, "Tool:\n %s\n\nParams:\n", getTask()->getName());
    for ( int i=1; i<argc; i++ ) {
        fprintf(stream, "  %s\n", argv[i]);
    }
    
    fprintf(stream, "\n");
    
    fprintf(stream, "Cmd:\n%s\n", getBFCorrectionTask()->getCmd());
    fprintf(stream, "\n");
}

}}}}} // namespace rstools::batch::plugins::bfcorrection::tool
