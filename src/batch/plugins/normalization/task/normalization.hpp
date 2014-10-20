#ifndef rstools_rsbatch_plugin_normalization_task_normalization_h
#define rstools_rsbatch_plugin_normalization_task_normalization_h

#include <iostream>
#include "batch/util/rsunixtask.hpp"

using namespace rstools::batch::util;

namespace rstools {
namespace batch {
namespace plugins {
namespace normalization {
namespace task {
    
class Normalization : public RSUnixTask {

public: 
    Normalization(const char* code, const char* name);
    
    char* getCmd();
};

}}}}} // namespace rstools::batch::plugins::normalization::task

#endif
