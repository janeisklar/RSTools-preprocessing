#ifndef rstools_rsbatch_plugin_reorientation_tool_reorientation_h
#define rstools_rsbatch_plugin_reorientation_tool_reorientation_h

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include "batch/util/rstool.hpp"
#include "../task/reorientation.hpp"

using namespace rstools::batch::util;

namespace rstools {
namespace batch {
namespace plugins {
namespace reorientation {
namespace tool {
    
class Reorientation : public RSTool {

public:
    void destroy();
    bool isEverythingFine();
    rsUIInterface* createUI();
    void printCallString(FILE *stream);
    
protected:
    void _parseParams(int argc, char * argv[]);
    void _init();
    virtual void _run();
    
    rstools::batch::plugins::reorientation::task::Reorientation* getReorientationTask();
    
    bool executionSuccessful;
    
};

}}}}} // namespace rstools::batch::plugins::reorientation::tool

#endif
