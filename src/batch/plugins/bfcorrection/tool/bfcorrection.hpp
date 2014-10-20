#ifndef rstools_rsbatch_plugin_bfcorrection_tool_bfcorrection_h
#define rstools_rsbatch_plugin_bfcorrection_tool_bfcorrection_h

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include "batch/util/rsunixtool.hpp"
#include "../task/bfcorrection.hpp"

using namespace rstools::batch::util;

namespace rstools {
namespace batch {
namespace plugins {
namespace bfcorrection {
namespace tool {
    
class BFCorrection : public RSUnixTool {

public:
    void destroy();
    rsUIInterface* createUI();
    
protected:
    void _init();    
};

}}}}} // namespace rstools::batch::plugins::bfcorrection::tool

#endif
