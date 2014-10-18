#ifndef rstools_rsbatch_plugin_regressors_tool_regressors_h
#define rstools_rsbatch_plugin_regressors_tool_regressors_h

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include "batch/util/rstool.hpp"
#include "../task/regressors.hpp"

using namespace rstools::batch::util;

namespace rstools {
namespace batch {
namespace plugins {
namespace regressors {
namespace tool {
    
class Regressors : public RSTool {

public:
    void destroy();
    bool isEverythingFine();
    rsUIInterface* createUI();
    void printCallString(FILE *stream);
    
protected:
    void _parseParams(int argc, char * argv[]);
    void _init();
    virtual void _run();
    
    rstools::batch::plugins::regressors::task::Regressors* getRegressorsTask();
    
    bool executionSuccessful;
    
};

}}}}} // namespace rstools::batch::plugins::regressors::tool

#endif
