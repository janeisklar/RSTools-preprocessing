#include "transformation.hpp"
#include "utils/rsstring.h"

using namespace rstools::batch::util;

namespace rstools {
namespace batch {
namespace plugins {
namespace transformation {
namespace tool {
    
void Transformation::_init()
{
    rsArgument *input = this->getTask()->getArgument("input");
    rsArgument *output = this->getTask()->getArgument("output");
    rsArgument *reference = this->getTask()->getArgument("reference");
    rsArgument *transformationType = this->getTask()->getArgument("transformationType");
    
    if ( input == NULL ) {
        fprintf(stderr, "An input needs to be specified!\n");
        this->executionSuccessful = false;
    }
    
    if ( output == NULL ) {
        fprintf(stderr, "An output needs to be specified!\n");
        this->executionSuccessful = false;
    }
    
    if ( transformationType == NULL ) {
        fprintf(stderr, "A transformationType needs to be specified!\n");
        this->executionSuccessful = false;
    }
    
    if ( reference == NULL ) {
        fprintf(stderr, "A reference volume needs to be specified!\n");
        this->executionSuccessful = false;
    }
}

void Transformation::destroy()
{}

rsUIInterface* Transformation::createUI()
{    
    rsUIOption *o;
    rsUIInterface* interface = rsUINewInterface();
    interface->description   = rsString("Transformation (ANTs' WarpImageMultiTransform)");
    
    o = rsUINewOption();
    o->name                = rsString("input");
    o->shorthand           = 'i';
    o->type                = G_OPTION_ARG_FILENAME;
    o->cli_description     = rsString("path to the dataset which is to be transformed");
    o->cli_arg_description = rsString("<volume>");
    rsUIAddOption(interface, o);
    
    o = rsUINewOption();
    o->name                = rsString("4dinput");
    o->shorthand           = '4';
    o->cli_description     = rsString("whether the input is a 4D-dataset");
    rsUIAddOption(interface, o);
    
    o = rsUINewOption();
    o->name                = rsString("output");
    o->shorthand           = 'o';
    o->type                = G_OPTION_ARG_FILENAME;
    o->cli_description     = rsString("path of the resulting transformed dataset");
    o->cli_arg_description = rsString("<volume>");
    rsUIAddOption(interface, o);
    
    o = rsUINewOption();
    o->name                = rsString("reference");
    o->shorthand           = 'r';
    o->type                = G_OPTION_ARG_FILENAME;
    o->cli_description     = rsString("rescale the output to have the same dimensions as this reference dataset");
    o->cli_arg_description = rsString("<volume>");
    rsUIAddOption(interface, o);

    o = rsUINewOption();
    o->name                = rsString("transformationType");
    o->type                = G_OPTION_ARG_STRING;
    o->cli_description     = rsString("type of transformation");
    o->cli_arg_description = rsString("<type>");
    o->defaultValue        = rsString("epi2mni");
    rsUIOptionValue allowedValues[] = {
      {rsString("epi2epitpl"), rsString("Transform from epi-space to epi-template-space")},
      {rsString("epi2mni"),    rsString("Transform from epi-space to MNI-space")},
      {rsString("epitpl2mni"), rsString("Transform from epi-template-space to MNI-space")},
      {rsString("epitpl2epi"), rsString("Transform from epi-template-space to epi-space")},
      {rsString("mni2epi"),    rsString("Transform from MNI-space to epi-space")},
      {rsString("mni2epitpl"), rsString("Transform from MNI-space to epi-template-space")},
      NULL
    };
    rsUISetOptionValues(o, allowedValues);
    rsUIAddOption(interface, o);
    
    o = rsUINewOption();
    o->name                = rsString("epi2EpiTemplateWarp");
    o->type                = G_OPTION_ARG_FILENAME;
    o->group               = RS_UI_GROUP_EXTENDED;
    o->cli_description     = rsString("path to the warp to the epi template");
    o->cli_arg_description = rsString("<volume>");
    o->defaultValue        = rsString("${epi2EpiTemplateWarp}");
    rsUIAddOption(interface, o);
        
    o = rsUINewOption();
    o->name                = rsString("epi2EpiTemplateInvWarp");
    o->type                = G_OPTION_ARG_FILENAME;
    o->group               = RS_UI_GROUP_EXTENDED;
    o->cli_description     = rsString("path to the inverse warp from the epi template");
    o->cli_arg_description = rsString("<volume>");
    o->defaultValue        = rsString("${epi2EpiTemplateInvWarp}");
    rsUIAddOption(interface, o);
    
    o = rsUINewOption();
    o->name                = rsString("epi2EpiTemplateAffine");
    o->type                = G_OPTION_ARG_FILENAME;
    o->group               = RS_UI_GROUP_EXTENDED;
    o->cli_description     = rsString("path to the affine matrix for transforming the epi to the epi template");
    o->cli_arg_description = rsString("<volume>");
    o->defaultValue        = rsString("${epi2EpiTemplateAffine}");
    rsUIAddOption(interface, o);
    
    o = rsUINewOption();
    o->name                = rsString("epiTemplateWarp");
    o->type                = G_OPTION_ARG_FILENAME;
    o->group               = RS_UI_GROUP_EXTENDED;
    o->cli_description     = rsString("path to the warp from the epi template to the MNI template");
    o->cli_arg_description = rsString("<volume>");
    o->defaultValue        = rsString("${epiTemplateWarp}");
    rsUIAddOption(interface, o);
        
    o = rsUINewOption();
    o->name                = rsString("epiTemplateInvWarp");
    o->type                = G_OPTION_ARG_FILENAME;
    o->group               = RS_UI_GROUP_EXTENDED;
    o->cli_description     = rsString("path to the warp from the epi template to the MNI template");
    o->cli_arg_description = rsString("<volume>");
    o->defaultValue        = rsString("${epiTemplateInvWarp}");
    rsUIAddOption(interface, o);
    
    o = rsUINewOption();
    o->name                = rsString("epiTemplateAffine");
    o->type                = G_OPTION_ARG_FILENAME;
    o->group               = RS_UI_GROUP_EXTENDED;
    o->cli_description     = rsString("path to the affine matrix for transforming the epi template to the MNI template");
    o->cli_arg_description = rsString("<volume>");
    o->defaultValue        = rsString("${epiTemplateAffine}");
    rsUIAddOption(interface, o);
    
    return interface;
}

}}}}} // namespace rstools::batch::plugins::transformation::tool
