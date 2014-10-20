#ifndef rstools_rsbatch_plugin_regressors_tool_regressors_h
#define rstools_rsbatch_plugin_regressors_tool_regressors_h

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include "batch/util/rsunixtool.hpp"
#include "../task/regressors.hpp"

using namespace rstools::batch::util;

namespace rstools {
namespace batch {
namespace plugins {
namespace regressors {
namespace tool {
    
class Regressors : public RSUnixTool {

public:
    void destroy();
    rsUIInterface* createUI();
    
protected:
    void _init();
};

}}}}} // namespace rstools::batch::plugins::regressors::tool

#endif
