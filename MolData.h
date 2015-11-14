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
#ifndef __MOLDATA_H
#define __MOLDATA_H

#include <QFile>
#include <QFileInfo>
#include "GLConf.h"
#include "MolConf.h"

typedef char ELEMSTR[8];
typedef double POS[3];
typedef double *pdouble;

class MolData 
{
public :
    MolData(GLConf *, MolConf *);
    ~MolData();
    
    virtual void saveFile(char *) {};

    GLConf *GC;
    MolConf *MC;

    char FileName[512];

    int AllocOX;

    int MaxNIons;
    int NIons;
    ELEMSTR *Elem;
    POS   *R0;
    //POS   *R;
    int   *Num;
    double XMin, XMax, YMin, YMax, ZMin, ZMax;

#ifndef __NOSTICK__
    int NSticks, MaxNSticks;
    int    *Ion1;
    int    *Ion2;
    double StickLengthCutoff;
#endif

    int Data3DOX;
    int NData3D[3];
    double OrgData3D[3];
    double MatData3D[3][3];
    double *Data3D;
    unsigned char *CubeIndex;
    double Data3DMaxAbs, Data3DSumAbs, Data3DSumSqrs;
    double IsosurfaceValue;

    // Isosurface variables
    int NTriangleMax[2];
    int NTriangle[2];
    pdouble Triangle0[2];
    //pdouble Triangle[2];
    pdouble NormalVector0[2];
    //pdouble NormalVector[2];

    void loadIonConf();
    void identify();
#ifndef __NOSTICK__
    void makeSticks();
#endif
    void makeIsosurfaces(int*, double*);

    void allocMem(int);
    void freeMem();

    void rotate();
    void rotateX(double);
    void rotateY(double);
    void rotateZ(double);
    void unrotate();

    int ReadLine(FILE *, char *);

    void getRotatedPos(int, double *, double *, double *);
    double getBallRadius(int);
    unsigned long getBallColor(int);

    int replaceMolecules(MolData *);
    int replaceData3D(MolData *); 

static QString GetFileNameExtension(char *);
static QString GetFileBaseName(char *);
static void GetFileNameExtension(char *, QString &);
static void GetFileNameExtension(char *, char*);
static void GetFileBaseName(char *, char*);
};

#endif
