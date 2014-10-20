#include "reorientation.hpp"
#include "utils/rsstring.h"

using namespace rstools::batch::util;

namespace rstools {
namespace batch {
namespace plugins {
namespace reorientation {
namespace tool {
    
void Reorientation::_init()
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

void Reorientation::destroy()
{}

rsUIInterface* Reorientation::createUI()
{    
    rsUIOption *o;
    rsUIInterface* interface = rsUINewInterface();
    interface->description   = rsString("Reorientation (AFNI's 3dAxialize)");
    
    o = rsUINewOption();
    o->name                = rsString("input");
    o->shorthand           = 'i';
    o->type                = G_OPTION_ARG_FILENAME;
    o->cli_description     = rsString("path to the dataset which is to be reoriented");
    o->cli_arg_description = rsString("<volume>");
    rsUIAddOption(interface, o);
    
    o = rsUINewOption();
    o->name                = rsString("output");
    o->shorthand           = 'o';
    o->type                = G_OPTION_ARG_FILENAME;
    o->cli_description     = rsString("path to the resulting reoriented dataset");
    o->cli_arg_description = rsString("<volume>");
    rsUIAddOption(interface, o);
    
    o = rsUINewOption();
    o->name                = rsString("orientation");
    o->shorthand           = 'r';
    o->type                = G_OPTION_ARG_STRING;
    o->cli_description     = rsString("Orientation code for output. The code must be 3 letters, one each from the pairs {R,L} {A,P} {I,S}.  The first letter gives the orientation of the x-axis, the second the orientation of the y-axis, the third the z-axis: R = Right-to-left, L = Left-to-right, A = Anterior-to-posterior, P = Posterior-to-anterior, I = Inferior-to-superior, S = Superior-to-inferior");
    o->cli_arg_description = rsString("<orientation>");
    o->defaultValue        = rsString("LPI");
    rsUIAddOption(interface, o);
    
    return interface;
}

}}}}} // namespace rstools::batch::plugins::reorientation::tool
