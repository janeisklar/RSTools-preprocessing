#ifndef rstools_rsbatch_plugin_smoothing_task_smoothing_h
#define rstools_rsbatch_plugin_smoothing_task_smoothing_h

#include <iostream>
#include "batch/util/rsunixtask.hpp"

using namespace rstools::batch::util;

namespace rstools {
namespace batch {
namespace plugins {
namespace smoothing {
namespace task {
    
class Smoothing : public RSUnixTask {

public: 
    Smoothing(const char* code, const char* name);
    
    char* getCmd(bool asExecuted);
};

}}}}} // namespace rstools::batch::plugins::smoothing::task

#endif
