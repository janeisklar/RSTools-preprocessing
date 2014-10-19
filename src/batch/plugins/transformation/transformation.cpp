#include "transformation.hpp"

using namespace rstools::batch::util;

namespace rstools {
namespace batch {
namespace plugins {
namespace transformation {

Transformation::Transformation()
{}

void Transformation::registerPlugin()
{
    RSTool::registerTool(createTransformationToolRegistration());
    RSTool::registerXSDExtension(createTransformationToolXSDExtension());
}

rsToolRegistration* Transformation::createTransformationToolRegistration()
{
    rsToolRegistration* toolRegistration = (rsToolRegistration*)malloc(sizeof(rsToolRegistration));
    toolRegistration->name       = getName();
    toolRegistration->code       = getCode();
    toolRegistration->category   = "Spatial";
    toolRegistration->createTool = (rsToolToolCreator)Transformation::createTransformationTool;
    toolRegistration->createTask = (rsToolTaskCreator)Transformation::createTransformationTask;
    return toolRegistration;
}

rsXSDExtension* Transformation::createTransformationToolXSDExtension()
{
    rsXSDExtension* toolExtension = (rsXSDExtension*)malloc(sizeof(rsXSDExtension));
    toolExtension->name           = getCode();
    toolExtension->file           = RSTOOLS_DATA_DIR "/" PACKAGE "/jobs/plugins/transformation.xsdext";
    toolExtension->type           = getCode();
    return toolExtension;
}

const char* Transformation::getName()
{
    return "Transformation";
}

const char* Transformation::getCode()
{
    return "transformation";
}

const char* Transformation::getVersion()
{
    return RSTOOLS_VERSION_LABEL;
}

RSTool* Transformation::createTransformationTool()
{
    return (RSTool*)(new tool::Transformation());
}

RSTask* Transformation::createTransformationTask()
{
    return (RSTask*) new task::Transformation("transformation", "Transformation");
}

}}}} // namespace rstools::batch::plugins::transformation

Plugin* rsGetPlugin(void)
{
    return (Plugin*) new rstools::batch::plugins::transformation::Transformation();
}
