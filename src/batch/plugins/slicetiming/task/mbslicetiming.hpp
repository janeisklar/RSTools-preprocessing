#ifndef rstools_rsbatch_plugin_slicetiming_task_mbslicetiming_h
#define rstools_rsbatch_plugin_slicetiming_task_mbslicetiming_h

#include <iostream>
#include "batch/util/rstask.hpp"

using namespace rstools::batch::util;

namespace rstools {
namespace batch {
namespace plugins {
namespace slicetiming {
namespace task {
    
class MBSliceTiming : public RSTask {

public: 
    MBSliceTiming(const char* code, const char* name);
    
    char* getCmd();
};

}}}}} // namespace rstools::batch::plugins::slicetiming::task

#endif
