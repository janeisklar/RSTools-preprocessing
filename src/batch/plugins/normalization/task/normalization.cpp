#include "normalization.hpp"

using namespace rstools::batch::util;

namespace rstools {
namespace batch {
namespace plugins {
namespace normalization {
namespace task {
   
Normalization::Normalization(const char* code, const char* name) : RSTask(code, name)
{}

char* Normalization::getCmd() {
    
    // acquire parameters
    rsArgument *input                  = this->getArgument("input");
    rsArgument *mean                   = this->getArgument("mean");
    rsArgument *epiTemplate            = this->getArgument("epiTemplate");
    rsArgument *epi2EpiTemplateWarp    = this->getArgument("epi2EpiTemplateWarp");
    rsArgument *epi2EpiTemplateInvWarp = this->getArgument("epi2EpiTemplateInvWarp");
    rsArgument *epi2EpiTemplateAffine  = this->getArgument("epi2EpiTemplateAffine");
    rsArgument *transformationType     = this->getArgument("transformationType");
    rsArgument *similarityMetric       = this->getArgument("similarityMetric");
    rsArgument *maxIterations          = this->getArgument("maxIterations");
    rsArgument *maxAffineIterations    = this->getArgument("maxAffineIterations");
        
    const char *fslPath = this->getJob()->getArgument("fslPath")->value;
    const char *ANTSPATH = this->getJob()->getArgument("ANTSPATH")->value;
    
    // determine transformation parameters
    string transformationTypeStr = (transformationType==NULL)
                                   ? "GR"
                                   : transformationType->value;
    string transformationCmd;
    string regularizationionCmd;
    
    if ( transformationTypeStr == "EL" ) {
        transformationCmd = "Elast[1]";
        regularizationionCmd = "Gauss[3,0.5]";
    } else if ( transformationTypeStr == "SY" ) {
        transformationCmd = "SyN[1,2,0.05] --geodesic 2";
        regularizationionCmd = "Gauss[3,0.]";
    } else if ( transformationTypeStr == "S2" ) {
        transformationCmd = "SyN[1,2,0.05]";
        regularizationionCmd = "Gauss[3,0.]";
    } else if ( transformationTypeStr == "GR" ) {
        transformationCmd = "SyN[0.25]";
        regularizationionCmd = "Gauss[3,0]";
    } else if ( transformationTypeStr == "EX" ) {
        transformationCmd = "Exp[0.5,10]";
        regularizationionCmd = "Gauss[3,0.5]";
    } else if ( transformationTypeStr == "DD" ) {
        transformationCmd = "GreedyExp[0.5,10]";
        regularizationionCmd = "Gauss[3,0.5]";
    }
    
    // determine similarity metric parameters
    string similarityMetricStr = (similarityMetric==NULL)
                                 ? "PR"
                                 : similarityMetric->value;
    string metricCmd;
    string metricParamCmd;
    
    if ( similarityMetricStr == "PR" ) {
        metricCmd = "PR[";
        metricParamCmd = "1,4]";
    } else if ( similarityMetricStr == "CC" ) {
        metricCmd = "CC[";
        metricParamCmd = "1,5]";
    } else if ( similarityMetricStr == "MI" ) {
        metricCmd = "MI[";
        metricParamCmd = "1,32]";
    } else if ( similarityMetricStr == "MSQ" ) {
        metricCmd = "MSQ[";
        metricParamCmd = "1,0]";
    }
    
    // prepare values for the command
    const char *maxIterationsCmd       = (maxIterations==NULL)
                                         ? "30x90x20"
                                         : maxIterations->value;
    
    const char *maxAffineIterationsCmd = (maxAffineIterations==NULL)
                                         ? "10000x10000x10000x10000x10000"
                                         : maxAffineIterations->value;
    
    const char *meanCmd                = (mean==NULL)
                                         ? "$tmpdir/mean.nii"
                                         : mean->value;
    
    return rsStringConcat(
        "# create a temporary directory\n",
        "tmpdir=`mktemp -d 2>/dev/null || mktemp -d -t 'rstools-pps'`\n",
        "\n",
        "# compute mean\n",
        "fslmaths ", input->value, " -Tmean ", meanCmd, "\n",
        "\n",
        "# perform registration\n",
        ANTSPATH, "ANTS 3 -m ", metricCmd.c_str(), epiTemplate->value, ",", input->value, ",", metricParamCmd.c_str(), " -t ", transformationCmd.c_str(), " -r ", regularizationionCmd.c_str(), " -o $tmpdir/tpl -i ", maxIterationsCmd, " --use-Histogram-Matching --number-of-affine-iterations ", maxAffineIterationsCmd, " --MI-option 32x16000\n",
        "\n",
        "# save resulting transformation parameters\n",
        "cp $tmpdir/tplWarp.nii.gz ", epi2EpiTemplateWarp->value, "\n",
        "cp $tmpdir/tplInverseWarp.nii.gz ", epi2EpiTemplateInvWarp->value, "\n",
        "cp $tmpdir/tplAffine.txt ", epi2EpiTemplateAffine->value, "\n",
        "rm -rf $tmpdir",
        NULL
    );
}

}}}}} // namespace rstools::batch::plugins::normalization::task
