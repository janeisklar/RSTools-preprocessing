#include "reorientation.hpp"

using namespace rstools::batch::util;

namespace rstools {
namespace batch {
namespace plugins {
namespace reorientation {

Reorientation::Reorientation()
{}

void Reorientation::registerPlugin()
{
    RSTool::registerTool(createReorientationToolRegistration());
    RSTool::registerXSDExtension(createReorientationToolXSDExtension());
}

rsToolRegistration* Reorientation::createReorientationToolRegistration()
{
    rsToolRegistration* toolRegistration = (rsToolRegistration*)malloc(sizeof(rsToolRegistration));
    toolRegistration->name       = getName();
    toolRegistration->code       = getCode();
    toolRegistration->category   = "Util";
    toolRegistration->createTool = (rsToolToolCreator)Reorientation::createReorientationTool;
    toolRegistration->createTask = (rsToolTaskCreator)Reorientation::createReorientationTask;
    return toolRegistration;
}

rsXSDExtension* Reorientation::createReorientationToolXSDExtension()
{
    rsXSDExtension* toolExtension = (rsXSDExtension*)malloc(sizeof(rsXSDExtension));
    toolExtension->name           = getCode();
    toolExtension->file           = RSTOOLS_DATA_DIR "/" PACKAGE "/jobs/plugins/reorientation.xsdext";
    toolExtension->type           = getCode();
    return toolExtension;
}

const char* Reorientation::getName()
{
    return "Reorientation";
}

const char* Reorientation::getCode()
{
    return "reorientation";
}

const char* Reorientation::getVersion()
{
    return RSTOOLS_VERSION_LABEL;
}

RSTool* Reorientation::createReorientationTool()
{
    return (RSTool*)(new tool::Reorientation());
}

RSTask* Reorientation::createReorientationTask()
{
    return (RSTask*) new task::Reorientation("reorientation", "Reorientation");
}

}}}} // namespace rstools::batch::plugins::reorientation

Plugin* rsGetPlugin(void)
{
    return (Plugin*) new rstools::batch::plugins::reorientation::Reorientation();
}
