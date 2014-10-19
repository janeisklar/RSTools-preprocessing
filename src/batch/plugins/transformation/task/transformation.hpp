#ifndef rstools_rsbatch_plugin_transformation_task_transformation_h
#define rstools_rsbatch_plugin_transformation_task_transformation_h

#include <iostream>
#include "batch/util/rstask.hpp"

using namespace rstools::batch::util;

namespace rstools {
namespace batch {
namespace plugins {
namespace transformation {
namespace task {
    
class Transformation : public RSTask {

public: 
    Transformation(const char* code, const char* name);
    
    char* getCmd();
};

}}}}} // namespace rstools::batch::plugins::transformation::task

#endif
