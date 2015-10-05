#ifndef rstools_rsbatch_plugin_despiking_task_despiking_h
#define rstools_rsbatch_plugin_despiking_task_despiking_h

#include <iostream>
#include "batch/util/rsunixtask.hpp"

using namespace rstools::batch::util;

namespace rstools {
namespace batch {
namespace plugins {
namespace despiking {
namespace task {
    
class Despiking : public RSUnixTask {

public: 
    Despiking(const char* code, const char* name);
    
    char* getCmd(bool asExecuted);
};

}}}}} // namespace rstools::batch::plugins::despiking::task

#endif
