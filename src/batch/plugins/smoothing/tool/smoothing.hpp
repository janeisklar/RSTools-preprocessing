#ifndef rstools_rsbatch_plugin_smoothing_tool_smoothing_h
#define rstools_rsbatch_plugin_smoothing_tool_smoothing_h

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include "batch/util/rsunixtool.hpp"
#include "../task/smoothing.hpp"

using namespace rstools::batch::util;

namespace rstools {
namespace batch {
namespace plugins {
namespace smoothing {
namespace tool {
    
class Smoothing : public RSUnixTool {

public:
    void destroy();
    rsUIInterface* createUI();
    
protected:
    void _init();
    virtual bool _prepareStream();
    
};

}}}}} // namespace rstools::batch::plugins::smoothing::tool

#endif
