#ifndef rstools_rsbatch_plugin_normalization_task_newnormalization_h
#define rstools_rsbatch_plugin_normalization_task_newnormalization_h

#include <iostream>
#include "batch/util/rsunixtask.hpp"

using namespace rstools::batch::util;

namespace rstools {
namespace batch {
namespace plugins {
namespace normalization {
namespace task {
    
class NewNormalization : public RSUnixTask {

public: 
    NewNormalization(const char* code, const char* name);
    
    char* getCmd(bool asExecuted);
};

}}}}} // namespace rstools::batch::plugins::normalization::task

#endif
