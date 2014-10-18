#include "despiking.hpp"

using namespace rstools::batch::util;

namespace rstools {
namespace batch {
namespace plugins {
namespace despiking {

Despiking::Despiking()
{}

void Despiking::registerPlugin()
{
    RSTool::registerTool(createDespikingToolRegistration());
    RSTool::registerXSDExtension(createDespikingToolXSDExtension());
}

rsToolRegistration* Despiking::createDespikingToolRegistration()
{
    rsToolRegistration* toolRegistration = (rsToolRegistration*)malloc(sizeof(rsToolRegistration));
    toolRegistration->name       = getName();
    toolRegistration->code       = getCode();
    toolRegistration->category   = "Artifacts / Motion";
    toolRegistration->createTool = (rsToolToolCreator)Despiking::createDespikingTool;
    toolRegistration->createTask = (rsToolTaskCreator)Despiking::createDespikingTask;
    return toolRegistration;
}

rsXSDExtension* Despiking::createDespikingToolXSDExtension()
{
    rsXSDExtension* toolExtension = (rsXSDExtension*)malloc(sizeof(rsXSDExtension));
    toolExtension->name           = getCode();
    toolExtension->file           = RSTOOLS_DATA_DIR "/" PACKAGE "/jobs/plugins/despiking.xsdext";
    toolExtension->type           = getCode();
    return toolExtension;
}

const char* Despiking::getName()
{
    return "De-spiking";
}

const char* Despiking::getCode()
{
    return "despiking";
}

const char* Despiking::getVersion()
{
    return RSTOOLS_VERSION_LABEL;
}

RSTool* Despiking::createDespikingTool()
{
    return (RSTool*)(new tool::Despiking());
}

RSTask* Despiking::createDespikingTask()
{
    return (RSTask*) new task::Despiking("despiking", "De-spiking");
}

}}}} // namespace rstools::batch::plugins::despiking

Plugin* rsGetPlugin(void)
{
    return (Plugin*) new rstools::batch::plugins::despiking::Despiking();
}
