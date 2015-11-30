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
    void setUseNewANTS(bool useNewAnts);

protected:
    void _init();
    bool useNewAnts;
    virtual bool _prepareStream();
};

}}}}} // namespace rstools::batch::plugins::normalization::tool

#endif
