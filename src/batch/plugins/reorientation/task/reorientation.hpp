#ifndef rstools_rsbatch_plugin_reorientation_task_reorientation_h
#define rstools_rsbatch_plugin_reorientation_task_reorientation_h

#include <iostream>
#include "batch/util/rsunixtask.hpp"

using namespace rstools::batch::util;

namespace rstools {
namespace batch {
namespace plugins {
namespace reorientation {
namespace task {
    
class Reorientation : public RSUnixTask {

public: 
    Reorientation(const char* code, const char* name);
    
    char* getCmd();
};

}}}}} // namespace rstools::batch::plugins::reorientation::task

#endif
