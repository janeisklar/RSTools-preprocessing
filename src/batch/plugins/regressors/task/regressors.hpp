#ifndef rstools_rsbatch_plugin_regressors_task_regressors_h
#define rstools_rsbatch_plugin_regressors_task_regressors_h

#include <iostream>
#include "batch/util/rsunixtask.hpp"

using namespace rstools::batch::util;

namespace rstools {
namespace batch {
namespace plugins {
namespace regressors {
namespace task {
    
class Regressors : public RSUnixTask {

public: 
    Regressors(const char* code, const char* name);
    
    char* getCmd(bool asExecuted);
};

}}}}} // namespace rstools::batch::plugins::regressors::task

#endif
