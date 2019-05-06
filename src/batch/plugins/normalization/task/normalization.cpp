#include "normalization.hpp"
#include "config.h"

using namespace rstools::batch::util;

namespace rstools {
namespace batch {
namespace plugins {
namespace normalization {
namespace task {
   
Normalization::Normalization(const char* code, const char* name) : RSUnixTask(code, name)
{}

char* Normalization::getCmd(bool asExecuted) {
    
    // acquire parameters
    rsArgument *input                  = this->getArgument("input");
    rsArgument *meanStream             = this->getArgument("rsstream_output");
    rsArgument *mean                   = this->getArgument("mean");
    const char *brainMask              = this->getDefaultArgumentValue("brainMask");
    const char *epiTemplate            = this->getDefaultArgumentValue("epiTemplate");
    const char *epiTemplateWarp        = this->getDefaultArgumentValue("epiTemplateWarp");
    const char *epiTemplateInvWarp     = this->getDefaultArgumentValue("epiTemplateInvWarp");
    const char *epiTemplateAffine      = this->getDefaultArgumentValue("epiTemplateAffine");
    const char *epi2EpiTemplateWarp    = this->getDefaultArgumentValue("epi2EpiTemplateWarp");
    const char *epi2EpiTemplateInvWarp = this->getDefaultArgumentValue("epi2EpiTemplateInvWarp");
    const char *epi2EpiTemplateAffine  = this->getDefaultArgumentValue("epi2EpiTemplateAffine");
    rsArgument *transformationType     = this->getArgument("transformationType");
    rsArgument *similarityMetric       = this->getArgument("similarityMetric");
    rsArgument *maxIterations          = this->getArgument("maxIterations");
    rsArgument *maxAffineIterations    = this->getArgument("maxAffineIterations");
    rsArgument *stripskull             = this->getArgument("stripskull");
        
    const char *fslPath     = this->getJob()->getArgument("fslPath")->value;
    const char *ANTSPATH    = this->getJob()->getArgument("ANTSPATH")->value;
    const char *afniPath    = this->getJob()->getArgument("afniPath")->value;
    const char *rstoolsPath = RSTOOLS_EXECUTABLES_PATH;
    
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
    
    const char *meanOut = (mean==NULL)
                          ? "$tmpdir/mean.nii"
                          : (asExecuted ? meanStream->value : mean->value);

    const char *meanIn  = (mean==NULL)
                          ? "$tmpdir/mean.nii"
                          : mean->value;
    
    const char *logKernelPath =  DATA_PATH "/" PACKAGE "/utils/logkernel_0.3.nii.gz";
    
    string source = "$tmpdir/skullstripped_input.nii";
    string target = "$tmpdir/skullstripped_tpl.nii";
    string stripskullCmd = "";
    
    if ( stripskull != NULL ) {
        source = "$tmpdir/skullstripped_input.nii";
        target = "$tmpdir/skullstripped_tpl.nii";
        stripskullCmd = rsStringConcat(
            "\n",
            "# compute EPI template edges\n",
            fslPath, "/fslmaths ", epiTemplate, " -kernel file ", logKernelPath, " -fmeanu $tmpdir/edges_tpl.nii\n",
            "\n",
            "# compute EPI edges\n",
            rstoolsPath, "/rszeropadding -i ", meanIn, " -o $tmpdir/padded_input.nii -a 5 -b 5 -c 5 -d 5 -e 5 -f 5\n",
            fslPath, "/fslmaths $tmpdir/padded_input.nii -kernel file ", logKernelPath, " -fmeanu $tmpdir/edges_input.nii\n",
            "\n",
            "# register EPI edges to EPI template edges\n",
            ANTSPATH, "ANTS 3 -m ", metricCmd.c_str(), "$tmpdir/edges_tpl.nii,$tmpdir/edges_input.nii,", metricParamCmd.c_str(), " -t ", transformationCmd.c_str(), " -r ", regularizationionCmd.c_str(), " -o $tmpdir/tpl -i ", maxIterationsCmd, " --use-Histogram-Matching --number-of-affine-iterations ", maxAffineIterationsCmd, " --MI-option 32x16000\n",
            "\n",
            "# warp brain mask\n",
            ANTSPATH, "WarpImageMultiTransform 3 ", brainMask, " $tmpdir/brainmask_tpl.nii -R $tmpdir/edges_tpl.nii -i ", epiTemplateAffine, " ", epiTemplateInvWarp,"\n",
            ANTSPATH, "WarpImageMultiTransform 3 ", brainMask, " $tmpdir/brainmask_input.nii -R ", meanIn, " -i $tmpdir/tplAffine.txt $tmpdir/tplInverseWarp.nii.gz -i ", epiTemplateAffine, " ", epiTemplateInvWarp,"\n",
            "\n",
            "# create epi template mask\n",
            fslPath, "/fslmaths ", epiTemplate, " -mas $tmpdir/brainmask_tpl.nii $tmpdir/brainmasked_tpl.nii\n",
            "csfValue=$(", fslPath, "/fslstats $tmpdir/brainmasked_tpl.nii -k $tmpdir/brainmask_tpl.nii -p 95)\n",
            fslPath, "/fslmaths $tmpdir/brainmask_tpl.nii -binv -mul $csfValue $tmpdir/brainmask_inv_tpl.nii\n",
            fslPath, "/fslmaths $tmpdir/brainmasked_tpl.nii -add $tmpdir/brainmask_inv_tpl.nii ", target.c_str(), "\n",
            "\n",
            "# create epi mask\n",
            fslPath, "/fslmaths ", meanIn, " -mas $tmpdir/brainmask_input.nii $tmpdir/brainmasked_input.nii\n",
            "csfValue=$(", fslPath, "/fslstats $tmpdir/brainmasked_input.nii -k $tmpdir/brainmask_input.nii -p 95)\n",
            fslPath, "/fslmaths $tmpdir/brainmask_input.nii -binv -mul $csfValue $tmpdir/brainmask_inv_input.nii\n",
            fslPath, "/fslmaths $tmpdir/brainmasked_input.nii -add $tmpdir/brainmask_inv_input.nii ", source.c_str(), "\n",
            NULL
        );
    }
    
    return rsStringConcat(
        "# create a temporary directory\n",
        "tmpdir=`mktemp -d 2>/dev/null || mktemp -d -t 'rstools-pps'`\n",
        "\n",
        "# compute mean\n",
        fslPath, "/fslmaths ", input->value, " -Tmean ", meanOut, "\n",
        stripskullCmd.c_str(),
        "\n",
        "# perform registration\n",
        ANTSPATH, "ANTS 3 -m ", metricCmd.c_str(), target.c_str(), ",", source.c_str(), ",", metricParamCmd.c_str(), " -t ", transformationCmd.c_str(), " -r ", regularizationionCmd.c_str(), " -o $tmpdir/tpl -i ", maxIterationsCmd, " --use-Histogram-Matching --number-of-affine-iterations ", maxAffineIterationsCmd, " --MI-option 32x16000\n",
        "\n",
        "# save resulting transformation parameters\n",
        "cp $tmpdir/tplWarp.nii.gz ", epi2EpiTemplateWarp, "\n",
        "cp $tmpdir/tplInverseWarp.nii.gz ", epi2EpiTemplateInvWarp, "\n",
        "cp $tmpdir/tplAffine.txt ", epi2EpiTemplateAffine, "\n",
        "rm -rf $tmpdir",
        NULL
    );
}

}}}}} // namespace rstools::batch::plugins::normalization::task
