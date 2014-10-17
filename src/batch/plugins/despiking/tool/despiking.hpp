#ifndef rstools_rsbatch_plugin_despiking_tool_despiking_h
#define rstools_rsbatch_plugin_despiking_tool_despiking_h

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include "batch/util/rstool.hpp"
#include "../task/despiking.hpp"

using namespace rstools::batch::util;

namespace rstools {
namespace batch {
namespace plugins {
namespace despiking {
namespace tool {
    
class Despiking : public RSTool {

public:
    void destroy();
    bool isEverythingFine();
    rsUIInterface* createUI();
    void printCallString(FILE *stream);
    
protected:
    void _parseParams(int argc, char * argv[]);
    void _init();
    virtual void _run();
    
    rstools::batch::plugins::despiking::task::Despiking* getDespikingTask();
    
    bool executionSuccessful;
    
};

}}}}} // namespace rstools::batch::plugins::despiking::tool

#endif
