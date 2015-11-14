/* *************************************************************************
bymol, molecular visualization software, 2011 - 
developed by Bokwon Yoon, PhD, School of Physics, Georgia Tech.

It is based on the software 3DView which is originally developed also
by Bokwon Yoon in 1998, and upgraded by himself thereafter.

This header comments must not be deleted even after any modification of this
software.
For any derivation from this software, you must include this header 
in the beginning of each source code file.
**************************************************************************** */
#ifndef __I_INFO_H
#define __I_INFO_H

#include "MolData.h"

class I_info : public MolData
{
public :
    I_info(const char *fn, GLConf *, MolConf *);
    ~I_info();
    
    int ExistOX;

    void readI_info(char *);
    int  countIons(char *);
    int  readIons(char *);
};

#endif
