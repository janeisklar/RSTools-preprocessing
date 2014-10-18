#include "regressors.hpp"

using namespace rstools::batch::util;

namespace rstools {
namespace batch {
namespace plugins {
namespace regressors {

Regressors::Regressors()
{}

void Regressors::registerPlugin()
{
    RSTool::registerTool(createRegressorsToolRegistration());
    RSTool::registerXSDExtension(createRegressorsToolXSDExtension());
}

rsToolRegistration* Regressors::createRegressorsToolRegistration()
{
    rsToolRegistration* toolRegistration = (rsToolRegistration*)malloc(sizeof(rsToolRegistration));
    toolRegistration->name       = getName();
    toolRegistration->code       = getCode();
    toolRegistration->category   = "Util";
    toolRegistration->createTool = (rsToolToolCreator)Regressors::createRegressorsTool;
    toolRegistration->createTask = (rsToolTaskCreator)Regressors::createRegressorsTask;
    return toolRegistration;
}

rsXSDExtension* Regressors::createRegressorsToolXSDExtension()
{
    rsXSDExtension* toolExtension = (rsXSDExtension*)malloc(sizeof(rsXSDExtension));
    toolExtension->name           = getCode();
    toolExtension->file           = RSTOOLS_DATA_DIR "/" PACKAGE "/jobs/plugins/regressors.xsdext";
    toolExtension->type           = getCode();
    return toolExtension;
}

const char* Regressors::getName()
{
    return "Merge Regressors";
}

const char* Regressors::getCode()
{
    return "regressors";
}

const char* Regressors::getVersion()
{
    return RSTOOLS_VERSION_LABEL;
}

RSTool* Regressors::createRegressorsTool()
{
    return (RSTool*)(new tool::Regressors());
}

RSTask* Regressors::createRegressorsTask()
{
    return (RSTask*) new task::Regressors("regressors", "Merge Regressors");
}

}}}} // namespace rstools::batch::plugins::regressors

Plugin* rsGetPlugin(void)
{
    return (Plugin*) new rstools::batch::plugins::regressors::Regressors();
}
