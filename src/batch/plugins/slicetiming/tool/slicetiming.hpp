#ifndef rstools_rsbatch_plugin_slicetiming_tool_slicetiming_h
#define rstools_rsbatch_plugin_slicetiming_tool_slicetiming_h

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include "batch/util/rstool.hpp"
#include "../task/slicetiming.hpp"

using namespace rstools::batch::util;

namespace rstools {
namespace batch {
namespace plugins {
namespace slicetiming {
namespace tool {
    
class SliceTiming : public RSTool {

public:
    void destroy();
    bool isEverythingFine();
    rsUIInterface* createUI();
    void printCallString(FILE *stream);
    void setMultibandActive(bool mbActive);
    
protected:
    void _parseParams(int argc, char * argv[]);
    void _init();
    virtual void _run();
    bool multibandActive;
    
    rstools::batch::plugins::slicetiming::task::SliceTiming* getSliceTimingTask();
    
    bool executionSuccessful;
    
};

}}}}} // namespace rstools::batch::plugins::unix::tool

#endif
