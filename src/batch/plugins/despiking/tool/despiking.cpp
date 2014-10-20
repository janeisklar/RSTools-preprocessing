#include "despiking.hpp"
#include "utils/rsstring.h"

using namespace rstools::batch::util;

namespace rstools {
namespace batch {
namespace plugins {
namespace despiking {
namespace tool {
    
void Despiking::_init()
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

void Despiking::destroy()
{}

rsUIInterface* Despiking::createUI()
{    
    rsUIOption *o;
    rsUIInterface* interface = rsUINewInterface();
    interface->description   = rsString("De-spiking (AFNI's 3dDespike)");
    
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
    o->name                = rsString("NEW");
    o->shorthand           = 'n';
    o->group               = RS_UI_GROUP_EXTENDED;
    o->cli_description     = rsString("Use the 'new' method for computing the fit, which should be faster than the L1 method for long time series (200+ time points); however, the results are similar but NOT identical");
    rsUIAddOption(interface, o);
    
    o = rsUINewOption();
    o->name                = rsString("corder");
    o->shorthand           = 'c';
    o->type                = G_OPTION_ARG_INT;
    o->group               = RS_UI_GROUP_EXTENDED;
    o->cli_description     = rsString("The curve fit order. For more information refer to AFNI.");
    o->cli_arg_description = rsString("<corder>");
    rsUIAddOption(interface, o);
    
    return interface;
}

}}}}} // namespace rstools::batch::plugins::despiking::tool
