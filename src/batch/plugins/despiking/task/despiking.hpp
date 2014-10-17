#ifndef rstools_rsbatch_plugin_despiking_task_despiking_h
#define rstools_rsbatch_plugin_despiking_task_despiking_h

#include <iostream>
#include "batch/util/rstask.hpp"

using namespace rstools::batch::util;

namespace rstools {
namespace batch {
namespace plugins {
namespace despiking {
namespace task {
    
class Despiking : public RSTask {

public: 
    Despiking(const char* code, const char* name);
    
    char* getCmd();
};

}}}}} // namespace rstools::batch::plugins::despiking::task

#endif
