#include "normalization.hpp"
#include "utils/rsstring.h"
#include "batch/util/rsunix.hpp"

using namespace rstools::batch::util;

namespace rstools {
namespace batch {
namespace plugins {
namespace normalization {
namespace tool {
    
void Normalization::_parseParams(int argc, char * argv[])
{   
    this->executionSuccessful = true;
}
    
void Normalization::_init()
{
    rsArgument *input = this->getTask()->getArgument("input");
    
    if ( input == NULL ) {
        fprintf(stderr, "An input needs to be specified!\n");
        this->executionSuccessful = false;
    }
}

void Normalization::destroy()
{}

bool Normalization::isEverythingFine()
{
    return this->executionSuccessful;
}

rstools::batch::plugins::normalization::task::Normalization* Normalization::getNormalizationTask()
{
    return (rstools::batch::plugins::normalization::task::Normalization*)this->getTask();
}

void Normalization::_run()
{
    this->executionSuccessful = rsExecuteUnixCommand(this->getNormalizationTask()->getCmd());
}

rsUIInterface* Normalization::createUI()
{    
    rsUIOption *o;
    rsUIInterface* interface = rsUINewInterface();
    interface->description   = rsString("Normalization (ANTs)");
    
    o = rsUINewOption();
    o->name                = rsString("input");
    o->shorthand           = 'i';
    o->type                = G_OPTION_ARG_FILENAME;
    o->cli_description     = rsString("path to a 3D/4D volume for which normalization is to be computed");
    o->cli_arg_description = rsString("<volume>");
    rsUIAddOption(interface, o);
    
    o = rsUINewOption();
    o->name                = rsString("mean");
    o->shorthand           = 'm';
    o->type                = G_OPTION_ARG_FILENAME;
    o->cli_description     = rsString("path where the mean image of the input volume is saved to");
    o->cli_arg_description = rsString("<volume>");
    rsUIAddOption(interface, o);
    
    o = rsUINewOption();
    o->name                = rsString("epiTemplate");
    o->type                = G_OPTION_ARG_FILENAME;
    o->group               = RS_UI_GROUP_EXTENDED;
    o->cli_description     = rsString("path of the epi template used for registration");
    o->cli_arg_description = rsString("<volume>");
    o->defaultValue        = rsString("${epiTemplate}");
    rsUIAddOption(interface, o);
    
    o = rsUINewOption();
    o->name                = rsString("epi2EpiTemplateWarp");
    o->type                = G_OPTION_ARG_FILENAME;
    o->group               = RS_UI_GROUP_EXTENDED;
    o->cli_description     = rsString("output path of the resulting warp to the epi template");
    o->cli_arg_description = rsString("<volume>");
    o->defaultValue        = rsString("${epi2EpiTemplateWarp}");
    rsUIAddOption(interface, o);
        
    o = rsUINewOption();
    o->name                = rsString("epi2EpiTemplateInvWarp");
    o->type                = G_OPTION_ARG_FILENAME;
    o->group               = RS_UI_GROUP_EXTENDED;
    o->cli_description     = rsString("output path of the resulting inverse warp from the epi template");
    o->cli_arg_description = rsString("<volume>");
    o->defaultValue        = rsString("${epi2EpiTemplateInvWarp}");
    rsUIAddOption(interface, o);
    
    o = rsUINewOption();
    o->name                = rsString("epi2EpiTemplateAffine");
    o->type                = G_OPTION_ARG_FILENAME;
    o->group               = RS_UI_GROUP_EXTENDED;
    o->cli_description     = rsString("output path of the resulting affine transformation matrix to the epi template");
    o->cli_arg_description = rsString("<volume>");
    o->defaultValue        = rsString("${epi2EpiTemplateAffine}");
    rsUIAddOption(interface, o);
    
    o = rsUINewOption();
    o->name                = rsString("transformationType");
    o->type                = G_OPTION_ARG_STRING;
    o->group               = RS_UI_GROUP_EXTENDED;
    o->cli_description     = rsString("Type of transformation model used for registration");
    o->cli_arg_description = rsString("<type>");
    o->defaultValue        = rsString("GR");
    rsUIOptionValue allowedValues[] = {
      {rsString("EL"),  rsString("Elastic transformation model (less deformation possible)")},
      {rsString("SY"),  rsString("SyN with time (default) with arbitrary number of time points in time discretization")},
      {rsString("S2"),  rsString("SyN with time optimized specifically for 2 time points in the time discretization")},
      {rsString("GR"),  rsString("Greedy SyN")},
      {rsString("EX"),  rsString("Exponential")},
      {rsString("DD"),  rsString("Diffeomorphic Demons style exponential mapping")},
      NULL
    };
    rsUISetOptionValues(o, allowedValues);
    rsUIAddOption(interface, o);
    
    o = rsUINewOption();
    o->name                = rsString("similarityMetric");
    o->type                = G_OPTION_ARG_STRING;
    o->group               = RS_UI_GROUP_EXTENDED;
    o->cli_description     = rsString("Type of similarity metric used for registration.");
    o->cli_arg_description = rsString("<type>");
    o->defaultValue        = rsString("PR");
    rsUIOptionValue allowedValues2[] = {
      {rsString("CC"),  rsString("cross-correlation(intramodal only)")},
      {rsString("MI"),  rsString("mutual information")},
      {rsString("PR"),  rsString("probability mapping")},
      {rsString("MSQ"), rsString("mean square difference(intramodal only)")},
      NULL
    };
    rsUISetOptionValues(o, allowedValues2);
    rsUIAddOption(interface, o);
    
    o = rsUINewOption();
    o->name                = rsString("maxIterations");
    o->type                = G_OPTION_ARG_INT;
    o->group               = RS_UI_GROUP_EXTENDED;
    o->cli_description     = rsString("Maximum number of iterations for all registration stages");
    o->cli_arg_description = rsString("<n>x<n>x<n>");
    o->defaultValue        = rsString("30x90x20");
    rsUIAddOption(interface, o);  
    
    o = rsUINewOption();
    o->name                = rsString("maxAffineIterations");
    o->type                = G_OPTION_ARG_INT;
    o->group               = RS_UI_GROUP_EXTENDED;
    o->cli_description     = rsString("Maximum number of iterations for all affine registration stages");
    o->cli_arg_description = rsString("<n>x<n>x<n>x<n>");
    o->defaultValue        = rsString("10000x10000x10000x10000x10000");
    rsUIAddOption(interface, o);
    
    return interface;
}

void Normalization::printCallString(FILE *stream)
{
    int argc;
    char **argv = getCallString(&argc);

    fprintf(stream, "Tool:\n %s\n\nParams:\n", getTask()->getName());
    for ( int i=1; i<argc; i++ ) {
        fprintf(stream, "  %s\n", argv[i]);
    }
    
    fprintf(stream, "\n");
    
    fprintf(stream, "Cmd:\n%s\n", getNormalizationTask()->getCmd());
    fprintf(stream, "\n");
}

}}}}} // namespace rstools::batch::plugins::normalization::tool
