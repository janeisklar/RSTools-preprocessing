#ifndef rstools_rsbatch_plugin_realignment_tool_realignment_h
#define rstools_rsbatch_plugin_realignment_tool_realignment_h

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include "batch/util/rsunixtool.hpp"
#include "../task/realignment.hpp"

using namespace rstools::batch::util;

namespace rstools {
namespace batch {
namespace plugins {
namespace realignment {
namespace tool {
    
class Realignment : public RSUnixTool {

public:
    void destroy();
    rsUIInterface* createUI();
    
protected:
    void _init();
    virtual bool _prepareStream();
    virtual void _moveOutputIfNecessary();
};

}}}}} // namespace rstools::batch::plugins::realignment::tool

#endif
