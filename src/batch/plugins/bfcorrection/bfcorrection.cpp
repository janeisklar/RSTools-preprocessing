#include "bfcorrection.hpp"

using namespace rstools::batch::util;

namespace rstools {
namespace batch {
namespace plugins {
namespace bfcorrection {

BFCorrection::BFCorrection()
{}

void BFCorrection::registerPlugin()
{
    RSTool::registerTool(createBFCorrectionToolRegistration());
    RSTool::registerXSDExtension(createBFCorrectionToolXSDExtension());
}

rsToolRegistration* BFCorrection::createBFCorrectionToolRegistration()
{
    rsToolRegistration* toolRegistration = (rsToolRegistration*)malloc(sizeof(rsToolRegistration));
    toolRegistration->name       = getName();
    toolRegistration->code       = getCode();
    toolRegistration->createTool = (rsToolToolCreator)BFCorrection::createBFCorrectionTool;
    toolRegistration->createTask = (rsToolTaskCreator)BFCorrection::createBFCorrectionTask;
    return toolRegistration;
}

rsXSDExtension* BFCorrection::createBFCorrectionToolXSDExtension()
{
    rsXSDExtension* toolExtension = (rsXSDExtension*)malloc(sizeof(rsXSDExtension));
    toolExtension->name           = getCode();
    toolExtension->file           = RSTOOLS_DATA_DIR "/" PACKAGE "/jobs/plugins/bfcorrection.xsdext";
    toolExtension->type           = getCode();
    return toolExtension;
}

const char* BFCorrection::getName()
{
    return "Bias Field Correction";
}

const char* BFCorrection::getCode()
{
    return "bfcorrection";
}

const char* BFCorrection::getVersion()
{
    return RSTOOLS_VERSION_LABEL;
}

RSTool* BFCorrection::createBFCorrectionTool()
{
    return (RSTool*)(new tool::BFCorrection());
}

RSTask* BFCorrection::createBFCorrectionTask()
{
    return (RSTask*) new task::BFCorrection("bfcorrection", "Bias Field Correction");
}

}}}} // namespace rstools::batch::plugins::bfcorrection

Plugin* rsGetPlugin(void)
{
    return (Plugin*) new rstools::batch::plugins::bfcorrection::BFCorrection();
}
