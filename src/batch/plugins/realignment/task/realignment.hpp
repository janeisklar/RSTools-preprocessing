#ifndef rstools_rsbatch_plugin_realignment_task_realignment_h
#define rstools_rsbatch_plugin_realignment_task_realignment_h

#include <iostream>
#include "batch/util/rsunixtask.hpp"

using namespace rstools::batch::util;

namespace rstools {
namespace batch {
namespace plugins {
namespace realignment {
namespace task {
    
class Realignment : public RSUnixTask {

public: 
    Realignment(const char* code, const char* name);
    
    virtual char* getCmd(bool asExecuted);
};

}}}}} // namespace rstools::batch::plugins::realignment::task

#endif
