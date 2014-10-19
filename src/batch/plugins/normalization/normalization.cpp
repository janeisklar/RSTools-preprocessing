#include "normalization.hpp"

using namespace rstools::batch::util;

namespace rstools {
namespace batch {
namespace plugins {
namespace normalization {

Normalization::Normalization()
{}

void Normalization::registerPlugin()
{
    RSTool::registerTool(createNormalizationToolRegistration());
    RSTool::registerXSDExtension(createNormalizationToolXSDExtension());
}

rsToolRegistration* Normalization::createNormalizationToolRegistration()
{
    rsToolRegistration* toolRegistration = (rsToolRegistration*)malloc(sizeof(rsToolRegistration));
    toolRegistration->name       = getName();
    toolRegistration->code       = getCode();
    toolRegistration->category   = "Spatial";
    toolRegistration->createTool = (rsToolToolCreator)Normalization::createNormalizationTool;
    toolRegistration->createTask = (rsToolTaskCreator)Normalization::createNormalizationTask;
    return toolRegistration;
}

rsXSDExtension* Normalization::createNormalizationToolXSDExtension()
{
    rsXSDExtension* toolExtension = (rsXSDExtension*)malloc(sizeof(rsXSDExtension));
    toolExtension->name           = getCode();
    toolExtension->file           = RSTOOLS_DATA_DIR "/" PACKAGE "/jobs/plugins/normalization.xsdext";
    toolExtension->type           = getCode();
    return toolExtension;
}

const char* Normalization::getName()
{
    return "Normalization";
}

const char* Normalization::getCode()
{
    return "normalization";
}

const char* Normalization::getVersion()
{
    return RSTOOLS_VERSION_LABEL;
}

RSTool* Normalization::createNormalizationTool()
{
    return (RSTool*)(new tool::Normalization());
}

RSTask* Normalization::createNormalizationTask()
{
    return (RSTask*) new task::Normalization("normalization", "Normalization");
}

}}}} // namespace rstools::batch::plugins::normalization

Plugin* rsGetPlugin(void)
{
    return (Plugin*) new rstools::batch::plugins::normalization::Normalization();
}
