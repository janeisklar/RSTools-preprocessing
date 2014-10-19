#ifndef rstools_rsbatch_plugin_normalization_tool_normalization_h
#define rstools_rsbatch_plugin_normalization_tool_normalization_h

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include "batch/util/rstool.hpp"
#include "../task/normalization.hpp"

using namespace rstools::batch::util;

namespace rstools {
namespace batch {
namespace plugins {
namespace normalization {
namespace tool {
    
class Normalization : public RSTool {

public:
    void destroy();
    bool isEverythingFine();
    rsUIInterface* createUI();
    void printCallString(FILE *stream);
    
protected:
    void _parseParams(int argc, char * argv[]);
    void _init();
    virtual void _run();
    
    rstools::batch::plugins::normalization::task::Normalization* getNormalizationTask();
    
    bool executionSuccessful;
    
};

}}}}} // namespace rstools::batch::plugins::normalization::tool

#endif
