#include "smoothing.hpp"

using namespace rstools::batch::util;

namespace rstools {
namespace batch {
namespace plugins {
namespace smoothing {

Smoothing::Smoothing()
{}

void Smoothing::registerPlugin()
{
    RSTool::registerTool(createSmoothingToolRegistration());
    RSTool::registerXSDExtension(createSmoothingToolXSDExtension());
}

rsToolRegistration* Smoothing::createSmoothingToolRegistration()
{
    rsToolRegistration* toolRegistration = (rsToolRegistration*)malloc(sizeof(rsToolRegistration));
    toolRegistration->name       = getName();
    toolRegistration->code       = getCode();
    toolRegistration->category   = "Spatial";
    toolRegistration->createTool = (rsToolToolCreator)Smoothing::createSmoothingTool;
    toolRegistration->createTask = (rsToolTaskCreator)Smoothing::createSmoothingTask;
    return toolRegistration;
}

rsXSDExtension* Smoothing::createSmoothingToolXSDExtension()
{
    rsXSDExtension* toolExtension = (rsXSDExtension*)malloc(sizeof(rsXSDExtension));
    toolExtension->name           = getCode();
    toolExtension->file           = RSTOOLS_DATA_DIR "/" PACKAGE "/jobs/plugins/smoothing.xsdext";
    toolExtension->type           = getCode();
    return toolExtension;
}

const char* Smoothing::getName()
{
    return "Smoothing (FSL)";
}

const char* Smoothing::getCode()
{
    return "smoothing";
}

const char* Smoothing::getVersion()
{
    return RSTOOLS_VERSION_LABEL;
}

RSTool* Smoothing::createSmoothingTool()
{
    return (RSTool*)(new tool::Smoothing());
}

RSTask* Smoothing::createSmoothingTask()
{
    return (RSTask*) new task::Smoothing("smoothing", "Smoothing (FSL)");
}

}}}} // namespace rstools::batch::plugins::smoothing

Plugin* rsGetPlugin(void)
{
    return (Plugin*) new rstools::batch::plugins::smoothing::Smoothing();
}
