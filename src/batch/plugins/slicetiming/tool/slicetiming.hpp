#ifndef rstools_rsbatch_plugin_slicetiming_tool_slicetiming_h
#define rstools_rsbatch_plugin_slicetiming_tool_slicetiming_h

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include "batch/util/rstool.hpp"
#include "../task/slicetiming.hpp"

#define RSTOOLS_FSL_SLICETIMING_INDEXING_BOTTOM_UP 1
#define RSTOOLS_FSL_SLICETIMING_INDEXING_TOP_DOWN 2

#define RSTOOLS_FSL_SLICETIMING_ACQUISITION_DIRECTION_X 1
#define RSTOOLS_FSL_SLICETIMING_ACQUISITION_DIRECTION_Y 2
#define RSTOOLS_FSL_SLICETIMING_ACQUISITION_DIRECTION_Z 3

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
    
protected:
    void _parseParams(int argc, char * argv[]);
    void _init();
    virtual void _run();
    
    rstools::batch::plugins::slicetiming::task::SliceTiming* getSliceTimingTask();
    
    bool executionSuccessful;
    
};

}}}}} // namespace rstools::batch::plugins::unix::tool

#endif
