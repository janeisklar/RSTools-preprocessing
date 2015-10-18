#include <batch/util/rstask.hpp>
#include "transformation.hpp"
#include "utils/rsstring.h"

using namespace rstools::batch::util;

namespace rstools {
namespace batch {
namespace plugins {
namespace transformation {
namespace task {
   
Transformation::Transformation(const char* code, const char* name) : RSUnixTask(code, name)
{}

char* Transformation::getCmd(bool asExecuted) {
    
    // acquire necessary parameters
    const char *input                  = this->getArgument("input")->value;
    const char *output                 = asExecuted ? this->getArgument("rsstream_output")->value : this->getArgument("output")->value;
    const char *reference              = this->getArgument("reference")->value;
    const char *epi2EpiTemplateWarp    = this->getArgument("epi2EpiTemplateWarp")->value;
    const char *epi2EpiTemplateInvWarp = this->getArgument("epi2EpiTemplateInvWarp")->value;
    const char *epi2EpiTemplateAffine  = this->getArgument("epi2EpiTemplateAffine")->value;
    const char *epiTemplateWarp        = this->getArgument("epiTemplateWarp")->value;
    const char *epiTemplateInvWarp     = this->getArgument("epiTemplateInvWarp")->value;
    const char *epiTemplateAffine      = this->getArgument("epiTemplateAffine")->value;
    rsArgument *transformationTypeArg  = this->getArgument("transformationType");
    const char *transformationType     = (transformationTypeArg == NULL)
                                         ? "epi2mni"
                                         : transformationTypeArg->value;
    const bool is4D                    = this->getArgument("4dinput") != NULL;
    const bool useAntsApplyTransforms  = this->getArgument("new") != NULL;
    
    const char *ANTSPATH = this->getJob()->getArgument("ANTSPATH")->value;
    const char *fslPath  = this->getJob()->getArgument("fslPath")->value;
    
    // assemble transformation
    std::stringstream trans;
    
    const bool fromEpi = rsStringStartsWith(transformationType, "epi2");
    const bool fromMNI = rsStringStartsWith(transformationType, "mni2");
    const bool toEpi   = rsStringEndsWith(transformationType, "2epi");
    const bool toMNI   = rsStringEndsWith(transformationType, "2mni");

    if (useAntsApplyTransforms) {

        trans << ANTSPATH << "antsApplyTransforms -e 3 -d 3 -i " << input << " -o " << output << " -r " << reference;

        if ( toEpi ) {
            trans << " -t \"[" << epi2EpiTemplateAffine << ",1]\" -t " << epi2EpiTemplateInvWarp;
        }

        if ( toMNI ) {
            trans << " -t " << epiTemplateWarp << " -t " << epiTemplateAffine;
        }

        if ( fromEpi ) {
            trans << " -t " << epi2EpiTemplateWarp << " -t " << epi2EpiTemplateAffine;
        }

        if ( fromMNI ) {
            trans << " -t \"[" << epiTemplateAffine << ",1]\" -t " << epiTemplateInvWarp;
        }

        return rsString(trans.str().c_str());

    } else {

        if ( toEpi ) {
            trans << " -i " << epi2EpiTemplateAffine << " " << epi2EpiTemplateInvWarp;
        }

        if ( toMNI ) {
            trans << " " << epiTemplateWarp << " " << epiTemplateAffine;
        }

        if ( fromEpi ) {
            trans << " " << epi2EpiTemplateWarp << " " << epi2EpiTemplateAffine;
        }

        if ( fromMNI ) {
            trans << " -i " << epiTemplateAffine << " " << epiTemplateInvWarp;
        }

        // build command
        if ( is4D ) {
            return rsStringConcat(
                "# create a temporary directory\n",
                "tmpdir=`mktemp -d 2>/dev/null || mktemp -d -t 'rstools-pps'`\n",
                "\n",
                "# split 4D-volume as ANTs requires us to process them individually\n",
                fslPath, "/fslsplit ", input," $tmpdir/vols -t\n",
                "for input in $(ls $tmpdir/vols*.nii);\n",
                "do\n",
                "   output=$(echo $input | sed -e 's/vols/'wvols'/g'); \n",
                "   ", ANTSPATH, "WarpImageMultiTransform 3 $input $output -R ", reference, trans.str().c_str(), "\n",
                "   rm -f $input\n",
                "done\n",
                "\n",
                "# merge and cleanup\n",
                fslPath, "/fslmerge -t ", output, " $tmpdir/wvols*.nii\n",
                "rm -rf $tmpdir",
                NULL
            );
        } else {
            return rsStringConcat(
                ANTSPATH, "WarpImageMultiTransform 3 ", input, " ", output, " -R ", reference, trans.str().c_str(),
                NULL
            );
        }
    }
}

}}}}} // namespace rstools::batch::plugins::transformation::task
