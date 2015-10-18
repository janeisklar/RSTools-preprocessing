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

    RSTool::registerTool(createNewNormalizationToolRegistration());
    RSTool::registerXSDExtension(createNewNormalizationToolXSDExtension());
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

rsToolRegistration* Normalization::createNewNormalizationToolRegistration()
{
    rsToolRegistration* toolRegistration = (rsToolRegistration*)malloc(sizeof(rsToolRegistration));
    toolRegistration->name       = getNewName();
    toolRegistration->code       = getNewCode();
    toolRegistration->category   = "Spatial";
    toolRegistration->createTool = (rsToolToolCreator)Normalization::createNewNormalizationTool;
    toolRegistration->createTask = (rsToolTaskCreator)Normalization::createNewNormalizationTask;
    return toolRegistration;
}

rsXSDExtension* Normalization::createNewNormalizationToolXSDExtension()
{
    rsXSDExtension* toolExtension = (rsXSDExtension*)malloc(sizeof(rsXSDExtension));
    toolExtension->name           = getNewCode();
    toolExtension->file           = RSTOOLS_DATA_DIR "/" PACKAGE "/jobs/plugins/newnormalization.xsdext";
    toolExtension->type           = getNewCode();
    return toolExtension;
}

const char* Normalization::getName()
{
    return "Normalization (old)";
}

const char* Normalization::getCode()
{
    return "normalization";
}

const char* Normalization::getNewName()
{
    return "Normalization";
}

const char* Normalization::getNewCode()
{
    return "newnormalization";
}

const char* Normalization::getVersion()
{
    return RSTOOLS_VERSION_LABEL;
}

RSTool* Normalization::createNormalizationTool()
{
    tool::Normalization *tool = new tool::Normalization();
    tool->setUseNewANTS(false);
    return (RSTool*)tool;
}

RSTool* Normalization::createNewNormalizationTool()
{
    tool::Normalization *tool = new tool::Normalization();
    tool->setUseNewANTS(true);
    return (RSTool*)tool;
}

RSTask* Normalization::createNormalizationTask()
{
    return (RSTask*) new task::Normalization("normalization", "Normalization (old)");
}

RSTask* Normalization::createNewNormalizationTask()
{
    return (RSTask*) new task::NewNormalization("newnormalization", "Normalization");
}

}}}} // namespace rstools::batch::plugins::normalization

Plugin* rsGetPlugin(void)
{
    return (Plugin*) new rstools::batch::plugins::normalization::Normalization();
}
