#ifndef rstools_rsbatch_plugin_transformation_tool_transformation_h
#define rstools_rsbatch_plugin_transformation_tool_transformation_h

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include "batch/util/rsunixtool.hpp"
#include "../task/transformation.hpp"

using namespace rstools::batch::util;

namespace rstools {
namespace batch {
namespace plugins {
namespace transformation {
namespace tool {
    
class Transformation : public RSUnixTool {

public:
    void destroy();
    rsUIInterface* createUI();
    
protected:
    void _init();
};

}}}}} // namespace rstools::batch::plugins::transformation::tool

#endif
