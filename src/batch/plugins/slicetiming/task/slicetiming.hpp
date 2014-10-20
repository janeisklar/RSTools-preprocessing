#ifndef rstools_rsbatch_plugin_slicetiming_task_slicetiming_h
#define rstools_rsbatch_plugin_slicetiming_task_slicetiming_h

#include <iostream>
#include "batch/util/rsunixtask.hpp"

using namespace rstools::batch::util;

namespace rstools {
namespace batch {
namespace plugins {
namespace slicetiming {
namespace task {
    
class SliceTiming : public RSUnixTask {

public: 
    SliceTiming(const char* code, const char* name);
    
    char* getCmd();
};

}}}}} // namespace rstools::batch::plugins::slicetiming::task

#endif
