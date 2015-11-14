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

#ifndef __VASPFILE_H
#define __VASPFILE_H

#include "MolData.h"

#define MAXNSPECIES 20

class POSCARFile : public MolData
{
public :
    POSCARFile(const char *, GLConf *, MolConf *);
    ~POSCARFile();

    char Comments[4096];
    double ScalingFactor;
    double LVector[3][3];
    double InvLV[3][3];
    int NSpecies;
    ELEMSTR Species[MAXNSPECIES];
    int SpeciesCount[MAXNSPECIES];
    int SelectiveDynamicsOX;
    char CartesianOX;

    double Min[3], Max[3];

    //POS     *Pos;
    //POSBOOL *PosOX;

    void calculateCellMinMax();
    void readPOSCARData(FILE *f);
    void readPOSCARFile(char *);
};

#endif
