#ifndef rstools_rsbatch_plugin_slicetiming_tool_slicetiming_h
#define rstools_rsbatch_plugin_slicetiming_tool_slicetiming_h

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include "batch/util/rsunixtool.hpp"
#include "../task/slicetiming.hpp"

using namespace rstools::batch::util;

namespace rstools {
namespace batch {
namespace plugins {
namespace slicetiming {
namespace tool {
    
class SliceTiming : public RSUnixTool {

public:
    void destroy();
    rsUIInterface* createUI();
    void setMultibandActive(bool mbActive);
    
protected:
    void _init();
    virtual bool _prepareStream();
    bool multibandActive;
};

}}}}} // namespace rstools::batch::plugins::unix::tool

#endif
