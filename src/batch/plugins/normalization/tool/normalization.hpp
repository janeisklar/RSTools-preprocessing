#ifndef rstools_rsbatch_plugin_normalization_tool_normalization_h
#define rstools_rsbatch_plugin_normalization_tool_normalization_h

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include "batch/util/rsunixtool.hpp"
#include "../task/normalization.hpp"

using namespace rstools::batch::util;

namespace rstools {
namespace batch {
namespace plugins {
namespace normalization {
namespace tool {
    
class Normalization : public RSUnixTool {

public:
    void destroy();
    rsUIInterface* createUI();
    
protected:
    void _init();
};

}}}}} // namespace rstools::batch::plugins::normalization::tool

#endif