#include "regressors.hpp"
#include <algorithm>
#include <string>

using namespace rstools::batch::util;

namespace rstools {
namespace batch {
namespace plugins {
namespace regressors {
namespace task {
   
Regressors::Regressors(const char* code, const char* name) : RSUnixTask(code, name)
{}

char* Regressors::getCmd() {
    
    rsArgument *input = this->getArgument("input");
    rsArgument *output = this->getArgument("output");
    
    string files = input->value;
    std::replace(files.begin(), files.end(), '\n', ' ');
    
    return rsStringConcat(
        "paste -d '\t' ", files.c_str(), " | sed -e 's/	/ /g' | sed -e 's/  / /g' | sed -e 's/  / /g' > ", output->value,
        NULL
    );
}

}}}}} // namespace rstools::batch::plugins::regressors::task
