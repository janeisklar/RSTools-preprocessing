#ifndef rstools_rsbatch_plugin_bfcorrection_tool_bfcorrection_h
#define rstools_rsbatch_plugin_bfcorrection_tool_bfcorrection_h

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include "batch/util/rstool.hpp"
#include "../task/bfcorrection.hpp"

using namespace rstools::batch::util;

namespace rstools {
namespace batch {
namespace plugins {
namespace bfcorrection {
namespace tool {
    
class BFCorrection : public RSTool {

public:
    void destroy();
    bool isEverythingFine();
    rsUIInterface* createUI();
    void printCallString(FILE *stream);
    
protected:
    void _parseParams(int argc, char * argv[]);
    void _init();
    virtual void _run();
    
    rstools::batch::plugins::bfcorrection::task::BFCorrection* getBFCorrectionTask();
    
    bool executionSuccessful;
    
};

}}}}} // namespace rstools::batch::plugins::bfcorrection::tool

#endif
