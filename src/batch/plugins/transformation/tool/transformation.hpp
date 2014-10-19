#ifndef rstools_rsbatch_plugin_transformation_tool_transformation_h
#define rstools_rsbatch_plugin_transformation_tool_transformation_h

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include "batch/util/rstool.hpp"
#include "../task/transformation.hpp"

using namespace rstools::batch::util;

namespace rstools {
namespace batch {
namespace plugins {
namespace transformation {
namespace tool {
    
class Transformation : public RSTool {

public:
    void destroy();
    bool isEverythingFine();
    rsUIInterface* createUI();
    void printCallString(FILE *stream);
    
protected:
    void _parseParams(int argc, char * argv[]);
    void _init();
    virtual void _run();
    
    rstools::batch::plugins::transformation::task::Transformation* getTransformationTask();
    
    bool executionSuccessful;
    
};

}}}}} // namespace rstools::batch::plugins::transformation::tool

#endif
