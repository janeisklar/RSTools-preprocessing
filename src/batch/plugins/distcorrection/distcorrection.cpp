#include "task/fmdistcorrection.hpp"
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
    RSTool::registerTool(createFMDistcorrectionToolRegistration());
    RSTool::registerXSDExtension(createFMDistcorrectionToolXSDExtension());
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

rsToolRegistration* Distcorrection::createFMDistcorrectionToolRegistration()
{
    rsToolRegistration* toolRegistration = (rsToolRegistration*)malloc(sizeof(rsToolRegistration));
    toolRegistration->name       = getFMName();
    toolRegistration->code       = getFMCode();
    toolRegistration->category   = "Artifacts / Motion";
    toolRegistration->createTool = (rsToolToolCreator)Distcorrection::createFMDistcorrectionTool;
    toolRegistration->createTask = (rsToolTaskCreator)Distcorrection::createFMDistcorrectionTask;
    return toolRegistration;
}

rsXSDExtension* Distcorrection::createFMDistcorrectionToolXSDExtension()
{
    rsXSDExtension* toolExtension = (rsXSDExtension*)malloc(sizeof(rsXSDExtension));
    toolExtension->name           = getFMCode();
    toolExtension->file           = RSTOOLS_DATA_DIR "/" PACKAGE "/jobs/plugins/fmdistcorrection.xsdext";
    toolExtension->type           = getFMCode();
    return toolExtension;
}

const char* Distcorrection::getName()
{
    return "Distortion Correction (Voxel-displacement map)";
}

const char* Distcorrection::getCode()
{
    return "distcorrection";
}

const char* Distcorrection::getFMName()
{
    return "Distortion Correction (Fieldmap)";
}

const char* Distcorrection::getFMCode()
{
    return "fmdistcorrection";
}

const char* Distcorrection::getVersion()
{
    return RSTOOLS_VERSION_LABEL;
}

RSTool* Distcorrection::createDistcorrectionTool()
{
    tool::Distcorrection *tool = new tool::Distcorrection();
    tool->setMode(tool::SHIFTMAP);
    return (RSTool*)tool;
}


RSTool* Distcorrection::createFMDistcorrectionTool()
{
    tool::Distcorrection *tool = new tool::Distcorrection();
    tool->setMode(tool::FIELDMAP);
    return (RSTool*)tool;
}

RSTask* Distcorrection::createDistcorrectionTask()
{
    return (RSTask*) new task::Distcorrection("distcorrection", "Distortion Correction (Voxel-displacement map)");
}

RSTask* Distcorrection::createFMDistcorrectionTask()
{
    return (RSTask*) new task::FMDistcorrection("fmdistcorrection", "Distortion Correction (Fieldmap)");
}

}}}} // namespace rstools::batch::plugins::distcorrection

Plugin* rsGetPlugin(void)
{
    return (Plugin*) new rstools::batch::plugins::distcorrection::Distcorrection();
}
