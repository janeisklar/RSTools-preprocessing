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

enum DistorionCorrectionMode {
    FIELDMAP,
    SHIFTMAP
};

class Distcorrection : public RSUnixTool {

public:
    void destroy();
    rsUIInterface* createUI();
    void setMode(DistorionCorrectionMode mode);

protected:
    void _init();
    virtual bool _prepareStream();

    DistorionCorrectionMode  mode;
};

}}}}} // namespace rstools::batch::plugins::distcorrection::tool

#endif
