#ifndef rstools_rsbatch_plugin_distcorrection_tool_distcorrection_h
#define rstools_rsbatch_plugin_distcorrection_tool_distcorrection_h

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include "batch/util/rstool.hpp"
#include "../task/distcorrection.hpp"

using namespace rstools::batch::util;

namespace rstools {
namespace batch {
namespace plugins {
namespace distcorrection {
namespace tool {
    
class Distcorrection : public RSTool {

public:
    void destroy();
    bool isEverythingFine();
    rsUIInterface* createUI();
    void printCallString(FILE *stream);
    
protected:
    void _parseParams(int argc, char * argv[]);
    void _init();
    virtual void _run();
    
    rstools::batch::plugins::distcorrection::task::Distcorrection* getDistcorrectionTask();
    
    bool executionSuccessful;
    
};

}}}}} // namespace rstools::batch::plugins::distcorrection::tool

#endif
