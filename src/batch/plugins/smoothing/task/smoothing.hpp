#ifndef rstools_rsbatch_plugin_smoothing_task_smoothing_h
#define rstools_rsbatch_plugin_smoothing_task_smoothing_h

#include <iostream>
#include "batch/util/rstask.hpp"

using namespace rstools::batch::util;

namespace rstools {
namespace batch {
namespace plugins {
namespace smoothing {
namespace task {
    
class Smoothing : public RSTask {

public: 
    Smoothing(const char* code, const char* name);
    
    char* getCmd();
};

}}}}} // namespace rstools::batch::plugins::smoothing::task

#endif
