#ifndef rstools_rsbatch_plugin_distcorrection_tool_distcorrection_h
#define rstools_rsbatch_plugin_distcorrection_tool_distcorrection_h

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include "batch/util/rsunixtool.hpp"
#include "../task/distcorrection.hpp"

using namespace rstools::batch::util;

namespace rstools {
namespace batch {
namespace plugins {
namespace distcorrection {
namespace tool {
    
class Distcorrection : public RSUnixTool {

public:
    void destroy();
    rsUIInterface* createUI();
    
protected:
    void _init();
};

}}}}} // namespace rstools::batch::plugins::distcorrection::tool

#endif
