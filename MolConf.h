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

#ifndef __MOLCONF_H
#define __MOLCONF_H

#define MAX_ELEMENTS 25

#include <QtOpenGL>


class MolConf
{
public:

    int MolConfFileOX;

    MolConf();
    ~MolConf();

    void setDefaultMolConf();
    void loadMolConfFile(char *);
    int isMolConfFileLoaded() { return MolConfFileOX; }
    int identifyIon(char *, int);
    int getAtomicNumber(int);
    char *getElementName(int);
    double getBallRadius(int);
    unsigned long getBallColor(int);
    int checkStickLength(int, int, double);
    double GetStickLength(int, int);
    double getStickRadius(int, int);

    char MolConfFilePath[512];

    double BallRadiusFactor;
    double StickLengthFactor;
    double MaxStickLength;

    int NElements;
    char Element[MAX_ELEMENTS][8];
    int  Z[MAX_ELEMENTS];
    double BallRadius[MAX_ELEMENTS];
    unsigned long BallColor[MAX_ELEMENTS];
    double StickLength[MAX_ELEMENTS][MAX_ELEMENTS];
    double StickThickness[MAX_ELEMENTS][MAX_ELEMENTS];
    
    int IsosurfaceSumMode;
    double IsosurfaceCutoff;
    unsigned int IsosurfaceColor[2];


static const char ELEMENT[101][3];
static const double CVRADIUS[101];
static const unsigned int COLOR[101];


};

#endif


