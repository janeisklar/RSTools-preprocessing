#include "distcorrection.hpp"

using namespace rstools::batch::util;

namespace rstools {
namespace batch {
namespace plugins {
namespace distcorrection {

Distcorrection::Distcorrection()
{}

void Distcorrection::registerPlugin()
{
    RSTool::registerTool(createDistcorrectionToolRegistration());
    RSTool::registerXSDExtension(createDistcorrectionToolXSDExtension());
}

rsToolRegistration* Distcorrection::createDistcorrectionToolRegistration()
{
    rsToolRegistration* toolRegistration = (rsToolRegistration*)malloc(sizeof(rsToolRegistration));
    toolRegistration->name       = getName();
    toolRegistration->code       = getCode();
    toolRegistration->category   = "Artifacts / Motion";
    toolRegistration->createTool = (rsToolToolCreator)Distcorrection::createDistcorrectionTool;
    toolRegistration->createTask = (rsToolTaskCreator)Distcorrection::createDistcorrectionTask;
    return toolRegistration;
}

rsXSDExtension* Distcorrection::createDistcorrectionToolXSDExtension()
{
    rsXSDExtension* toolExtension = (rsXSDExtension*)malloc(sizeof(rsXSDExtension));
    toolExtension->name           = getCode();
    toolExtension->file           = RSTOOLS_DATA_DIR "/" PACKAGE "/jobs/plugins/distcorrection.xsdext";
    toolExtension->type           = getCode();
    return toolExtension;
}

const char* Distcorrection::getName()
{
    return "Distortion Correction";
}

const char* Distcorrection::getCode()
{
    return "distcorrection";
}

const char* Distcorrection::getVersion()
{
    return RSTOOLS_VERSION_LABEL;
}

RSTool* Distcorrection::createDistcorrectionTool()
{
    return (RSTool*)(new tool::Distcorrection());
}

RSTask* Distcorrection::createDistcorrectionTask()
{
    return (RSTask*) new task::Distcorrection("distcorrection", "Distortion Correction");
}

}}}} // namespace rstools::batch::plugins::distcorrection

Plugin* rsGetPlugin(void)
{
    return (Plugin*) new rstools::batch::plugins::distcorrection::Distcorrection();
}
