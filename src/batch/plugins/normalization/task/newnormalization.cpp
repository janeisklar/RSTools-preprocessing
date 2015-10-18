#include <batch/util/rstask.hpp>
#include "newnormalization.hpp"
#include "config.h"

using namespace rstools::batch::util;

namespace rstools {
namespace batch {
namespace plugins {
namespace normalization {
namespace task {

NewNormalization::NewNormalization(const char* code, const char* name) : RSUnixTask(code, name)
{}

char* NewNormalization::getCmd(bool asExecuted) {
    
    // acquire parameters
    rsArgument *input                  = this->getArgument("input");
    rsArgument *mean                   = this->getArgument("mean");
    const char *brainMask              = this->getDefaultArgumentValue("brainMask");
    const char *epiTemplate            = this->getDefaultArgumentValue("epiTemplate");
    const char *epiTemplateWarp        = this->getDefaultArgumentValue("epiTemplateWarp");
    const char *epiTemplateInvWarp     = this->getDefaultArgumentValue("epiTemplateInvWarp");
    const char *epiTemplateAffine      = this->getDefaultArgumentValue("epiTemplateAffine");
    const char *epi2EpiTemplateWarp    = this->getDefaultArgumentValue("epi2EpiTemplateWarp");
    const char *epi2EpiTemplateInvWarp = this->getDefaultArgumentValue("epi2EpiTemplateInvWarp");
    const char *epi2EpiTemplateAffine  = this->getDefaultArgumentValue("epi2EpiTemplateAffine");
    const char *nThreads               = this->getArgument("threads") == NULL ? rsString("1") : this->getArgument("threads")->value;

    const char *fslPath     = this->getJob()->getArgument("fslPath")->value;
    const char *ANTSPATH    = this->getJob()->getArgument("ANTSPATH")->value;
    const char *afniPath    = this->getJob()->getArgument("afniPath")->value;
    const char *rstoolsPath = RSTOOLS_EXECUTABLES_PATH;
    
    // prepare values for the command
    const char *meanCmd                = (mean==NULL)
                                         ? "$tmpdir/mean.nii"
                                         : mean->value;
    
    const char *logKernelPath =  DATA_PATH "/" PACKAGE "/utils/logkernel_0.3.nii.gz";

    string source = "$tmpdir/skullstripped_input.nii";
    string target = "$tmpdir/skullstripped_tpl.nii";
    string stripskullCmd = rsStringConcat(
        "\n",
        "# compute EPI template edges\n",
        fslPath, "/fslmaths ", epiTemplate, " -kernel file ", logKernelPath, " -fmeanu $tmpdir/edges_tpl.nii\n",
        "\n",
        "# compute EPI edges\n",
        rstoolsPath, "/rszeropadding -i ", meanCmd, " -o $tmpdir/padded_input.nii -a 5 -b 5 -c 5 -d 5 -e 5 -f 5\n",
        fslPath, "/fslmaths $tmpdir/padded_input.nii -kernel file ", logKernelPath, " -fmeanu $tmpdir/edges_input.nii\n",
        "\n",
        "# register EPI edges to EPI template edges\n",
        ANTSPATH, "/antsRegistrationSyN.sh -d 3 -f $tmpdir/edges_tpl.nii -m $tmpdir/edges_input.nii -o $tmpdir/tpl -n ", nThreads,
        "\n",
        "# warp brain mask\n",
        ANTSPATH, "antsApplyTransforms -d 3 -i ", brainMask, " -o $tmpdir/brainmask_tpl.nii -r $tmpdir/edges_tpl.nii -t \"[", epiTemplateAffine, ",1]\" -t ", epiTemplateInvWarp, "\n",
        ANTSPATH, "antsApplyTransforms -d 3 -i ", brainMask, " -o $tmpdir/brainmask_input.nii -r ", meanCmd, " -t \"[$tmpdir/tpl0GenericAffine.mat,1]\" $tmpdir/tpl1InverseWarp.nii.gz -t \"[", epiTemplateAffine, ",1]\" -t ", epiTemplateInvWarp, "\n",
        "\n",
        "# create epi template mask\n",
        fslPath, "/fslmaths ", epiTemplate, " -mas $tmpdir/brainmask_tpl.nii $tmpdir/brainmasked_tpl.nii\n",
        "csfValue=$(", fslPath, "/fslstats $tmpdir/brainmasked_tpl.nii -k $tmpdir/brainmask_tpl.nii -p 95)\n",
        fslPath, "/fslmaths $tmpdir/brainmask_tpl.nii -binv -mul $csfValue $tmpdir/brainmask_inv_tpl.nii\n",
        fslPath, "/fslmaths $tmpdir/brainmasked_tpl.nii -add $tmpdir/brainmask_inv_tpl.nii ", target.c_str(), "\n",
        "\n",
        "# create epi mask\n",
        fslPath, "/fslmaths ", meanCmd, " -mas $tmpdir/brainmask_input.nii $tmpdir/brainmasked_input.nii\n",
        "csfValue=$(", fslPath, "/fslstats $tmpdir/brainmasked_input.nii -k $tmpdir/brainmask_input.nii -p 95)\n",
        fslPath, "/fslmaths $tmpdir/brainmask_input.nii -binv -mul $csfValue $tmpdir/brainmask_inv_input.nii\n",
        fslPath, "/fslmaths $tmpdir/brainmasked_input.nii -add $tmpdir/brainmask_inv_input.nii ", source.c_str(), "\n",
        NULL
    );

    return rsStringConcat(
        "export ITK_GLOBAL_DEFAULT_NUMBER_OF_THREADS=", nThreads, "\n",
        "# create a temporary directory\n",
        "tmpdir=`mktemp -d 2>/dev/null || mktemp -d -t 'rstools-pps'`\n",
        "\n",
        "# compute mean\n",
        fslPath, "/fslmaths ", input->value, " -Tmean ", meanCmd, "\n",
        stripskullCmd.c_str(),
        "\n",
        "# perform registration\n",
        "## get the rigid part\n",
        ANTSPATH, "antsRegistrationSyN.sh -d 3 -f ", target.c_str(), " -m ", source.c_str(), " -o $tmpdir/final_tpl -t a -n ", nThreads, "\n",
        "## get the deformable part\n",
        ANTSPATH, "antsRegistration -d 3 --initial-moving-transform $tmpdir/final_tpl0GenericAffine.mat -m \"cc[", target.c_str(), ",", source.c_str(), ",1,2]\" -t 'SyN[0.25,3,0]' -c 100x70x50x20 -f 8x4x2x1 -s 3x2x1x0 -o $tmpdir/final_tpl\n",
        ANTSPATH, "ConvertTransformFile 3 $tmpdir/final_tpl0GenericAffine.mat $tmpdir/final_tpl0GenericAffine.txt\n",
        "\n",
        "# save resulting transformation parameters\n",
        "cp $tmpdir/final_tpl1Warp.nii.gz ", epi2EpiTemplateWarp, "\n",
        "cp $tmpdir/final_tpl1InverseWarp.nii.gz ", epi2EpiTemplateInvWarp, "\n",
        "cp $tmpdir/final_tpl0GenericAffine.txt ", epi2EpiTemplateAffine, "\n",
        "rm -rf $tmpdir",
        NULL
    );
}

}}}}} // namespace rstools::batch::plugins::normalization::task
