#ifndef rstools_rsbatch_plugin_realignment_tool_realignment_h
#define rstools_rsbatch_plugin_realignment_tool_realignment_h

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include "batch/util/rstool.hpp"
#include "../task/realignment.hpp"

using namespace rstools::batch::util;

namespace rstools {
namespace batch {
namespace plugins {
namespace realignment {
namespace tool {
    
class Realignment : public RSTool {

public:
    void destroy();
    bool isEverythingFine();
    rsUIInterface* createUI();
    void printCallString(FILE *stream);
    
protected:
    void _parseParams(int argc, char * argv[]);
    void _init();
    virtual void _run();
    
    rstools::batch::plugins::realignment::task::Realignment* getRealignmentTask();
    
    bool executionSuccessful;
    
};

}}}}} // namespace rstools::batch::plugins::realignment::tool

#endif
