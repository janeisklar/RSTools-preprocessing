#include "slicetiming.hpp"
#include "task/mbslicetiming.hpp"

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
    
    RSTool::registerTool(createMBSliceTimingToolRegistration());
    RSTool::registerXSDExtension(createMBSliceTimingToolXSDExtension());
}

rsToolRegistration* SliceTiming::createSliceTimingToolRegistration()
{
    rsToolRegistration* toolRegistration = (rsToolRegistration*)malloc(sizeof(rsToolRegistration));
    toolRegistration->name       = getName();
    toolRegistration->code       = getCode();
    toolRegistration->category   = "Temporal";
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

rsToolRegistration* SliceTiming::createMBSliceTimingToolRegistration()
{
    rsToolRegistration* toolRegistration = (rsToolRegistration*)malloc(sizeof(rsToolRegistration));
    toolRegistration->name       = "Slice Timing (Multiband)";
    toolRegistration->code       = "mbslicetiming";
    toolRegistration->category   = "Temporal";
    toolRegistration->createTool = (rsToolToolCreator)SliceTiming::createMBSliceTimingTool;
    toolRegistration->createTask = (rsToolTaskCreator)SliceTiming::createMBSliceTimingTask;
    return toolRegistration;
}

rsXSDExtension* SliceTiming::createMBSliceTimingToolXSDExtension()
{
    rsXSDExtension* toolExtension = (rsXSDExtension*)malloc(sizeof(rsXSDExtension));
    toolExtension->name           = "mbslicetiming";
    toolExtension->file           = RSTOOLS_DATA_DIR "/" PACKAGE "/jobs/plugins/mbslicetiming.xsdext";
    toolExtension->type           = "mbslicetiming";
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
    tool::SliceTiming *tool = new tool::SliceTiming();
    tool->setMultibandActive(false);
    return (RSTool*)tool;
}

RSTask* SliceTiming::createSliceTimingTask()
{
    return (RSTask*) new task::SliceTiming("slicetiming", "Slice Timing");
}

RSTask* SliceTiming::createMBSliceTimingTask()
{
    return (RSTask*) new task::MBSliceTiming("mbslicetiming", "Slice Timing (Multiband)");
}

RSTool* SliceTiming::createMBSliceTimingTool()
{
    tool::SliceTiming *tool = new tool::SliceTiming();
    tool->setMultibandActive(true);
    return (RSTool*)tool;
}

}}}} // namespace rstools::batch::plugins::slicetiming

Plugin* rsGetPlugin(void)
{
    return (Plugin*) new rstools::batch::plugins::slicetiming::SliceTiming();
}
