#ifndef rstools_rsbatch_plugin_realignment_task_realignment_h
#define rstools_rsbatch_plugin_realignment_task_realignment_h

#include <iostream>
#include "batch/util/rstask.hpp"

using namespace rstools::batch::util;

namespace rstools {
namespace batch {
namespace plugins {
namespace realignment {
namespace task {
    
class Realignment : public RSTask {

public: 
    Realignment(const char* code, const char* name);
    
    char* getCmd();
};

}}}}} // namespace rstools::batch::plugins::realignment::task

#endif
