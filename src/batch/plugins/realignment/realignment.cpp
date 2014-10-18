#include "realignment.hpp"

using namespace rstools::batch::util;

namespace rstools {
namespace batch {
namespace plugins {
namespace realignment {

Realignment::Realignment()
{}

void Realignment::registerPlugin()
{
    RSTool::registerTool(createRealignmentToolRegistration());
    RSTool::registerXSDExtension(createRealignmentToolXSDExtension());
}

rsToolRegistration* Realignment::createRealignmentToolRegistration()
{
    rsToolRegistration* toolRegistration = (rsToolRegistration*)malloc(sizeof(rsToolRegistration));
    toolRegistration->name       = getName();
    toolRegistration->code       = getCode();
    toolRegistration->createTool = (rsToolToolCreator)Realignment::createRealignmentTool;
    toolRegistration->createTask = (rsToolTaskCreator)Realignment::createRealignmentTask;
    return toolRegistration;
}

rsXSDExtension* Realignment::createRealignmentToolXSDExtension()
{
    rsXSDExtension* toolExtension = (rsXSDExtension*)malloc(sizeof(rsXSDExtension));
    toolExtension->name           = getCode();
    toolExtension->file           = RSTOOLS_DATA_DIR "/" PACKAGE "/jobs/plugins/realignment.xsdext";
    toolExtension->type           = getCode();
    return toolExtension;
}

const char* Realignment::getName()
{
    return "Realignment";
}

const char* Realignment::getCode()
{
    return "realignment";
}

const char* Realignment::getVersion()
{
    return RSTOOLS_VERSION_LABEL;
}

RSTool* Realignment::createRealignmentTool()
{
    return (RSTool*)(new tool::Realignment());
}

RSTask* Realignment::createRealignmentTask()
{
    return (RSTask*) new task::Realignment("realignment", "Realignment");
}

}}}} // namespace rstools::batch::plugins::realignment

Plugin* rsGetPlugin(void)
{
    return (Plugin*) new rstools::batch::plugins::realignment::Realignment();
}
