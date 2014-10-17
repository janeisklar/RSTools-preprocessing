#include "mbslicetiming.hpp"

using namespace rstools::batch::util;

namespace rstools {
namespace batch {
namespace plugins {
namespace slicetiming {
namespace task {
   
MBSliceTiming::MBSliceTiming(const char* code, const char* name) : RSTask(code, name)
{
}

char* MBSliceTiming::getCmd() {
    
    char *fslPath = this->getJob()->getArgument("fslPath")->value;
    char *cmd = rsStringConcat(fslPath, "/slicetimer", NULL);
    char *mean = NULL;
    char *in;
    char *out;
    
    // prepare the call for the slicetimer
    for ( vector<rsArgument*>::size_type j = 0; j != arguments.size(); j++ ) {
        rsArgument *arg = arguments[j];
                
        char *oldCmd = cmd;
        char *newCmd = NULL;
        
        if ( ! strcmp(arg->key, "in") ) {
            newCmd = rsStringConcat(" --in=", arg->value, NULL);
            in = arg->value;
        } else if ( !strcmp(arg->key, "out") ) {
            newCmd = rsStringConcat(" --out=", arg->value, NULL);
            out = arg->value;
        } else if ( !strcmp(arg->key, "tcustom") ) {
            newCmd = rsStringConcat(" --tcustom=", arg->value, NULL);
        } else if ( !strcmp(arg->key, "mean") ) {
            newCmd = rsString("");
            mean = arg->value;
        } else if ( !strcmp(arg->key, "direction") ) {
            if ( !strcmp(arg->value, "x") ) {
                newCmd = rsString(" --direction=1");
            } else if ( !strcmp(arg->value, "y") ) {
                newCmd = rsString(" --direction=2");
            } else {
                newCmd = rsString(" --direction=3");
            }
        } else {
            fprintf(stderr, "Option '%s' is an unknown argument for the slicetiming-tool\n", arg->key);
            newCmd = rsString("");
        }
        
        cmd = rsStringConcat(cmd, newCmd, NULL);
        
        rsFree(newCmd);
        rsFree(oldCmd);
    }
    
    // prepare the computation of the mean
    if ( mean != NULL ) {
        char *oldCmd = cmd;
        cmd = rsStringConcat(cmd, "\n", fslPath, "/fslmaths ", in, " -Tmean ", out, NULL);
        rsFree(oldCmd);
    }
    
    return cmd;
}

}}}}} // namespace rstools::batch::plugins::slicetiming::task
