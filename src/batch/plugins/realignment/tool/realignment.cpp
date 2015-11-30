#include <batch/util/rstask.hpp>
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
    o->name                = rsString("mean");
    o->shorthand           = 'm';
    o->type                = G_OPTION_ARG_FILENAME;
    o->cli_description     = rsString("optional path of a mean image that will be created after realigning the image");
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

bool Realignment::_prepareStream()
{
    // assemble temporary stream path
    streamName = rsStringConcat(tmpDirPath, "/stream.nii", NULL);

    // add stream to list of job arguments
    rsArgument *arg = (rsArgument*)malloc(sizeof(rsArgument));
    arg->key = rsString("rsstream_output");
    arg->value = rsString(streamName);
    getUnixTask()->addArgument(arg);

    // set the target path of the stream
    streamTarget = rsString(getUnixTask()->getArgument("output")->value);

    // read in header information of the input nifti
    inputNifti = nifti_image_read(getUnixTask()->getArgument("input")->value, false);

    // create stream
    return this->_createStream(streamName);
}

void Realignment::_moveOutputIfNecessary()
{
    if (streamName == NULL) {
        return;
    }

    // mcflirt will create some additional files that we'll have to move from
    // the temporary directory

    // copy .mat/* files
    char *matFilesSrc  = rsStringConcat(tmpDirPath, "/stream.nii.mat", NULL);
    char *matFilesDest = rsStringConcat(streamTarget, ".mat", NULL);

    char *cmd = (char*)rsMalloc(sizeof(char)*20000);
    sprintf(cmd, "/bin/rm -rf \'%s\'; /bin/cp -R -p \'%s\' \'%s\'", matFilesDest, matFilesSrc, matFilesDest);
    system(cmd);

    rsFree(matFilesSrc);
    rsFree(matFilesDest);

    // copy .par file
    char *parFilesSrc  = rsStringConcat(tmpDirPath, "/stream.nii.par", NULL);
    char *parFilesDest = rsStringConcat(streamTarget, ".par.txt", NULL);
    sprintf(cmd, "/bin/cp -f -p \'%s\' \'%s\'", parFilesSrc, parFilesDest);
    system(cmd);

    rsFree(parFilesSrc);
    rsFree(parFilesDest);
    rsFree(cmd);
}

}}}}} // namespace rstools::batch::plugins::realignment::tool
