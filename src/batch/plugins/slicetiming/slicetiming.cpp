#include "slicetiming.hpp"

using namespace rstools::batch::util;

namespace rstools {
namespace batch {
namespace plugins {
namespace slicetiming {

SliceTiming::SliceTiming()
{}

void SliceTiming::registerPlugin()
{
    RSTool::registerTool(createSliceTimingToolRegistration());
    RSTool::registerXSDExtension(createSliceTimingToolXSDExtension());
}

rsToolRegistration* SliceTiming::createSliceTimingToolRegistration()
{
    rsToolRegistration* toolRegistration = (rsToolRegistration*)malloc(sizeof(rsToolRegistration));
    toolRegistration->name       = getName();
    toolRegistration->code       = getCode();
    toolRegistration->createTool = (rsToolToolCreator)SliceTiming::createSliceTimingTool;
    toolRegistration->createTask = (rsToolTaskCreator)SliceTiming::createSliceTimingTask;
    return toolRegistration;
}
rsXSDExtension* SliceTiming::createSliceTimingToolXSDExtension()
{
    rsXSDExtension* toolExtension = (rsXSDExtension*)malloc(sizeof(rsXSDExtension));
    toolExtension->name           = getCode();
    toolExtension->file           = RSTOOLS_DATA_DIR "/" PACKAGE "/jobs/plugins/slicetiming.xsdext";
    toolExtension->type           = getCode();
    return toolExtension;
}

const char* SliceTiming::getName()
{
    return "Slice Timing";
}

const char* SliceTiming::getCode()
{
    return "slicetiming";
}

const char* SliceTiming::getVersion()
{
    return RSTOOLS_VERSION_LABEL;
}

RSTool* SliceTiming::createSliceTimingTool()
{
    return (RSTool*) new tool::SliceTiming();
}

RSTask* SliceTiming::createSliceTimingTask()
{
    return (RSTask*) new task::SliceTiming("slicetiming", "Slice Timing");
}

}}}} // namespace rstools::batch::plugins::slicetiming

Plugin* rsGetPlugin(void)
{
    return (Plugin*) new rstools::batch::plugins::slicetiming::SliceTiming();
}
