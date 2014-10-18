#ifndef rstools_rsbatch_plugin_smoothing_tool_smoothing_h
#define rstools_rsbatch_plugin_smoothing_tool_smoothing_h

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include "batch/util/rstool.hpp"
#include "../task/smoothing.hpp"

using namespace rstools::batch::util;

namespace rstools {
namespace batch {
namespace plugins {
namespace smoothing {
namespace tool {
    
class Smoothing : public RSTool {

public:
    void destroy();
    bool isEverythingFine();
    rsUIInterface* createUI();
    void printCallString(FILE *stream);
    
protected:
    void _parseParams(int argc, char * argv[]);
    void _init();
    virtual void _run();
    
    rstools::batch::plugins::smoothing::task::Smoothing* getSmoothingTask();
    
    bool executionSuccessful;
    
};

}}}}} // namespace rstools::batch::plugins::smoothing::tool

#endif
