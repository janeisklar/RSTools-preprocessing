#ifndef rstools_rsbatch_plugin_despiking_tool_despiking_h
#define rstools_rsbatch_plugin_despiking_tool_despiking_h

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include "batch/util/rsunixtool.hpp"
#include "../task/despiking.hpp"

using namespace rstools::batch::util;

namespace rstools {
namespace batch {
namespace plugins {
namespace despiking {
namespace tool {
    
class Despiking : public RSUnixTool {

public:
    void destroy();
    rsUIInterface* createUI();
    
protected:
    void _init();
    virtual bool _prepareStream();
};

}}}}} // namespace rstools::batch::plugins::despiking::tool

#endif
