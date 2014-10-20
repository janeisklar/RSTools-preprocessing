#ifndef rstools_rsbatch_plugin_reorientation_tool_reorientation_h
#define rstools_rsbatch_plugin_reorientation_tool_reorientation_h

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include "batch/util/rsunixtool.hpp"
#include "../task/reorientation.hpp"

using namespace rstools::batch::util;

namespace rstools {
namespace batch {
namespace plugins {
namespace reorientation {
namespace tool {
    
class Reorientation : public RSUnixTool {

public:
    void destroy();
    rsUIInterface* createUI();
    
protected:
    void _init();    
};

}}}}} // namespace rstools::batch::plugins::reorientation::tool

#endif
