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
#include <stdio.h>
#include <string.h>
#include <math.h>
#include "MolConf.h"
#include "MolData.h"
#include "MarchingCube.h"


QString MolData::GetFileNameExtension(char *fn)
{
   QFileInfo qi(fn);
   return QString(qi.completeSuffix());
}

QString MolData::GetFileBaseName(char *fn)
{
   QFileInfo qi(fn);
   return QString(qi.fileName());
}

void MolData::GetFileNameExtension(char *fn, QString &ext)
{
   QFileInfo qi(fn);
   ext = QString(qi.completeSuffix());
}

void MolData::GetFileNameExtension(char *fn, char *ext)
{
   QFileInfo qi(fn);
   strcpy(ext, (const char*)qi.completeSuffix().toLocal8Bit().constData());
}

void MolData::GetFileBaseName(char *fn, char *ext)
{
   QFileInfo qi(fn);
   strcpy(ext, (const char *)qi.fileName().toLocal8Bit().constData());
}

MolData::MolData(GLConf *gc, MolConf *mc)
{
    GC = gc;
    MC = mc;
    strcpy(FileName, "");

    NIons     = -1;
#ifndef __NOSTICK__
    NSticks   = -1;
    MaxNSticks = -1;
    StickLengthCutoff = 0.0;
#endif
    AllocOX   = 0;
    Data3DOX  = 0;
    Data3D    = 0;
    CubeIndex = 0;

    NTriangle[0] = NTriangle[1] = 0;
    NTriangleMax[0] = NTriangleMax[1] = 0;
}

MolData::~MolData()
{
    if (AllocOX == 1) freeMem();
}

void MolData::allocMem(int n)
{
    MaxNIons = n;
    Elem = new ELEMSTR[n];
    R0   = new POS[n];
    //R   = new POS[n];
    Num  = new int[n];

#ifndef __NOSTICK__
    if (n < 10000) MaxNSticks = n*20;
    else if (n < 100000) MaxNSticks = n*10;
    else MaxNSticks = n*6;
    Ion1   = new int[MaxNSticks];
    Ion2   = new int[MaxNSticks];
#endif

    AllocOX = 1;
}

void MolData::freeMem()
{
    delete[] Elem;
    delete[] R0;
    //delete[] R;
    delete[] Num;

#ifndef __NOSTICK__
    delete[] Ion1;
    delete[] Ion2;
#endif

    if (Data3D != 0) delete Data3D;
    if (CubeIndex != 0) delete CubeIndex;

    AllocOX = 0;
}

void MolData::loadIonConf()
{
    QFile f("3D_conf");

    if (f.exists()) {
        f.open(QIODevice::ReadOnly);
    }
}

void MolData::identify()
{
    int n, m, previon;

#ifndef __NOSTICK__
    int count, elemcount = 0;
    int elemlist[103]; 
    double r, slcut = 0.0;

    for (n = 0; n < 100; n++) {
        elemlist[n] = -1;
    }
#endif

    if (NIons > 0) {
        previon = 0; 
        XMin = YMin = ZMin = +1.0e+300;
        XMax = YMax = ZMax = -1.0e+300;
        for (n = 0; n < NIons; n++) {
#ifndef __NOSTICK__
            // Get Ion Type
            Num[n] = previon = MC->identifyIon((char *)Elem[n], previon);
            if (elemlist[Num[n]] < 0) {
                elemcount++;
                elemlist[Num[n]] = Num[n];
            } 
#endif
            if (XMin > R0[n][0]) XMin = R0[n][0];
            if (YMin > R0[n][1]) YMin = R0[n][1];
            if (ZMin > R0[n][2]) ZMin = R0[n][2];
            if (XMax < R0[n][0]) XMax = R0[n][0];
            if (YMax < R0[n][1]) YMax = R0[n][1];
            if (ZMax < R0[n][2]) ZMax = R0[n][2];
        }
#ifndef __NOSTICK__
        count = 0;
        for (n = 0; n < 100; n++) {
            if (elemlist[n] >= 0) {
                elemlist[count] = elemlist[n];
                count++;
            }
        } 

        for (n = 0; n < count; n++) {
            for (m = 0; m < count; m++) {
                r = MC->GetStickLength(elemlist[n], elemlist[m]);
                if (r > slcut) slcut = r;
            }
        }
        /*
        for (n = 0; n < elemcount-1; n++) {
            for (m = n+1; m < elemcount; m++) {
                r = MC->GetStickLength(elemlist[n], elemlist[m]);
                if (r > slcut) slcut = r;
            }
        }
        */
        StickLengthCutoff = slcut;
#endif        
    }
    rotate();
}

#ifndef __NOSTICK__

typedef struct {
    int LinkedList;
    int MyIndex;
    int Prev;
    int Next;
} LINK;

typedef struct {
    int MyIndex;
    int Count;
    int First;
    int Last;
} LINKEDLIST;

void LL_Add(LINKEDLIST *LL, int lln, LINK *L, int ln)
{
    if (LL[lln].Count == 0) {
        LL[lln].First = LL[lln].Last = ln;
        L[ln].LinkedList = lln;
        L[ln].Prev = -1;
        L[ln].Next = -1;
        LL[lln].Count++;
    } else {
        L[LL[lln].Last].Next = ln;
        L[ln].LinkedList = lln;
        L[ln].Prev = LL[lln].Last;
        L[ln].Next = -1;
        LL[lln].Last = ln;
        LL[lln].Count++;
    }
}

void MolData::makeSticks()
{
    int n, n1, n2, count, k;
    double x1, y1, z1, dx, dy, dz, rr, r;
    double lx, ly, lz, maxsl;
    int nx, ny, nz, m, mx, my, mz, mxm, mxp, mym, myp, mzm, mzp; 
    double delx, dely, delz;
    LINK *L;
    LINKEDLIST *LL;

    //printf("NIons = %d, Rcut = %f\n", NIons, StickLengthCutoff);
    if (NIons < 1000) {
        count = 0;
        for (n1 = 0; n1 < NIons; n1++) {
            for (n2 = n1+1; n2 < NIons; n2++) {
                dx = R0[n2][0]-R0[n1][0];
                dy = R0[n2][1]-R0[n1][1];
                dz = R0[n2][2]-R0[n1][2];
                rr = dx*dx + dy*dy + dz*dz;
                r = sqrt(rr);
                if (MC->checkStickLength(Num[n1], Num[n2], r)) {
                    Ion1[count]  = n1;
                    Ion2[count]  = n2;
                    count++;
                }
            }
        }
    } else {
        if (StickLengthCutoff < 1.0e-05) return;
        lx   = XMax-XMin;
        ly   = YMax-YMin;
        lz   = ZMax-ZMin;
        maxsl = StickLengthCutoff;
        nx = (int)ceil(lx/maxsl);
        ny = (int)ceil(ly/maxsl);
        nz = (int)ceil(lz/maxsl);
        delx = lx/(double)nx;
        dely = ly/(double)ny;
        delz = lz/(double)nz;
        L = new LINK[NIons];
        LL = new LINKEDLIST[nx*ny*nz];

        for (n = 0; n < nx*ny*nz; n++) {
            LL[n].MyIndex = n;
            LL[n].First = LL[n].Last = -1;
            LL[n].Count = 0;
        }

        for (n = 0; n < NIons; n++) {
            L[n].MyIndex = n;
            L[n].Prev = L[n].Next = -1;
            L[n].LinkedList = -1;
        }

        for (n = 0; n < NIons; n++) {
            mx = (int)floor((R0[n][0]-XMin)/delx);
            if (mx <   0) mx = 0;
            if (mx >= nx) mx = nx-1;
            my = (int)floor((R0[n][1]-YMin)/dely);
            if (my <   0) my = 0;
            if (my >= ny) my = ny-1;
            mz = (int)floor((R0[n][2]-ZMin)/delz);
            if (mz <   0) mz = 0;
            if (mz >= nz) mz = nz-1;
            m = mx*ny*nz+my*nz+mz;
            LL_Add(LL, m, L, n);
        }

        count = 0;
        for (n = 0; n < NIons; n++) {
            x1 = R0[n][0];
            y1 = R0[n][1];
            z1 = R0[n][2];
            m = L[n].LinkedList;
            mx = m/(ny*nz);
            m -= mx*(ny*nz);
            my = m/nz;
            mz = m-my*nz;
            mxm = (mx == 0) ? 0 : mx-1;
            mym = (my == 0) ? 0 : my-1;
            mzm = (mz == 0) ? 0 : mz-1;
            mxp = (mx == (nx-1)) ? nx-1 : mx+1;
            myp = (my == (ny-1)) ? ny-1 : my+1;
            mzp = (mz == (nz-1)) ? nz-1 : mz+1;
            for (mx = mxm; mx <= mxp; mx++) {
                for (my = mym; my <= myp; my++) {
                    for (mz = mzm; mz <= mzp; mz++) {
                        m = mx*ny*nz+my*nz+mz;
                        k = LL[m].First;
                        while (k >= 0) {
                            if (k >  n) {
                                dx = x1-R0[k][0];
                                dy = y1-R0[k][1];
                                dz = z1-R0[k][2];
                                rr = dx*dx + dy*dy + dz*dz;
                                r = sqrt(rr);
                                if (MC->checkStickLength(Num[n], Num[k], r)) {
                                    //Length[count] = r;       
                                    Ion1[count] = n;
                                    Ion2[count] = k;
                                    count++;
                                }
                            }
                            k = L[k].Next;
                        }
                    }
                }
            }
            
        }
      
        delete[] L;
        delete[] LL;
    }
    NSticks = count;
}
#endif

void MolData::makeIsosurfaces(int *nit, double*ival)
{
    int mode = MC->IsosurfaceSumMode;
    double isocutoff = MC->IsosurfaceCutoff;
    double cutoff = ((isocutoff < 0.0) || (isocutoff >= 1.0)) ? 0.9 : isocutoff;
    double ratio, val, x, upperval, lowerval;
    double sum;
    int count= 0, n, ntri;
    double isoval[2];

    lowerval = 0.0;
    upperval = Data3DMaxAbs;
    val = (lowerval+upperval)*0.5;
    do {
        sum = 0.0;
        for (n = 0; n < NData3D[0]*NData3D[1]*NData3D[2]; n++) {
            x = Data3D[n];
            if (x < 0.0) x = -x;
            if (x >= val) {
                if (mode == 0) sum += x;
                else sum += x*x;
            }
        }
        if (mode == 0) ratio = sum/Data3DSumAbs;
        else ratio = sum/Data3DSumSqrs;

        if (fabs(ratio-cutoff) > 0.005) {
            if (ratio > cutoff) lowerval = val; 
            else upperval = val;
            val = (lowerval+upperval)*0.5;
        }
        count++;
    } while ((fabs(ratio-cutoff) > 0.005) && (count < 20));

    *nit = count;
    *ival = IsosurfaceValue = val;
    /*
    char str[512];
    sprintf(str, "[iterations: %d] cutoff = %f", count, ratio);
    QMessageBox::about(0   , "isosurface cutoof", str);
    */

    isoval[0] = val;
    isoval[1] = -val;
    for (n = 0; n < 2; n++) {
        MakeTriCountTable();
        ::CubeIndex(Data3D, CubeIndex, NData3D[0], NData3D[1], NData3D[2], 
                    isoval[n]);
        ntri = TriCount(CubeIndex, NData3D[0], NData3D[1], NData3D[2]);

        if (NTriangle[n] < ntri) {
            if (NTriangle[n] > 0) {
                delete[] Triangle0[n];
                //delete[] Triangle[n];
                delete[] NormalVector0[n];
                //delete[] NormalVector[n];
            }
            NTriangleMax[n] = ntri;
            Triangle0[n] = new double[NTriangleMax[n]*9+10];
            //Triangle[n] = new double[NTriangleMax[n]*9+10];
            NormalVector0[n] = new double[NTriangleMax[n]*9+10];
            //NormalVector[n] = new double[NTriangleMax[n]*9+10];
        }
        NTriangle[n] = ntri;

        MakeTris2(Data3D, CubeIndex, NData3D[0], NData3D[1], NData3D[2], 
                 OrgData3D, MatData3D, 
                 isoval[n], Triangle0[n], NormalVector0[n]);
    }
    rotate();
}

void MolData::rotate()
{
    /*
    int k, l, n;
    double x, y, z;
    double rm[3][3];
    clock_t t1 = clock();

    for (k = 0; k < 3; k++) 
    for (l = 0; l < 3; l++) rm[k][l] = GC->RM[k][l];

    for (int n = 0; n < NIons; n++) {
        R[n][0] = rm[0][0]*R0[n][0]+rm[0][1]*R0[n][1]+rm[0][2]*R0[n][2];
        R[n][1] = rm[1][0]*R0[n][0]+rm[1][1]*R0[n][1]+rm[1][2]*R0[n][2];
        R[n][2] = rm[2][0]*R0[n][0]+rm[2][1]*R0[n][1]+rm[2][2]*R0[n][2];
    }

    for (l = 0; l < 2; l++) {
        for (n = 0; n < NTriangle[l]; n++) {
            for (k = 0; k < 3; k++) {
                x = Triangle0[l][9*n+3*k+0];
                y = Triangle0[l][9*n+3*k+1];
                z = Triangle0[l][9*n+3*k+2];
                Triangle[l][9*n+3*k+0] = rm[0][0]*x+rm[0][1]*y+rm[0][2]*z;
                Triangle[l][9*n+3*k+1] = rm[1][0]*x+rm[1][1]*y+rm[1][2]*z;
                Triangle[l][9*n+3*k+2] = rm[2][0]*x+rm[2][1]*y+rm[2][2]*z;
                x = NormalVector0[l][9*n+3*k+0];
                y = NormalVector0[l][9*n+3*k+1];
                z = NormalVector0[l][9*n+3*k+2];
                NormalVector[l][9*n+3*k+0] = rm[0][0]*x+rm[0][1]*y+rm[0][2]*z;
                NormalVector[l][9*n+3*k+1] = rm[1][0]*x+rm[1][1]*y+rm[1][2]*z;
                NormalVector[l][9*n+3*k+2] = rm[2][0]*x+rm[2][1]*y+rm[2][2]*z;
            }
        }
    }
    printf("time for rotation: %f s\n", (double)(clock()-t1)/(double)CLOCKS_PER_SEC);
    */
}

void MolData::rotateX(double angle)
{
    GC->rotateX(angle);
    rotate();
}

void MolData::rotateY(double angle)
{
    GC->rotateY(angle);
    rotate();
}

void MolData::rotateZ(double angle)
{
    GC->rotateZ(angle);
    rotate();
}

void MolData::unrotate()
{
    GC->unrotate();
    rotate();
}

void MolData::getRotatedPos(int n, double *x, double *y, double *z)
{
    ///*
    double x0, y0, z0;

    x0 = R0[n][0];
    y0 = R0[n][1];
    z0 = R0[n][2];
    
    *x = GC->RM[0][0]*x0+GC->RM[0][1]*y0+GC->RM[0][2]*z0;
    *y = GC->RM[1][0]*x0+GC->RM[1][1]*y0+GC->RM[1][2]*z0;
    *z = GC->RM[2][0]*x0+GC->RM[2][1]*y0+GC->RM[2][2]*z0;
    //*/

    /*
    *x = R[n][0];
    *y = R[n][1];
    *z = R[n][2];
    */
}

int MolData::ReadLine(FILE *f, char *buf)
{
    int c, n = 0;

    if (f == NULL) return 0;
    do {
        c = fgetc(f);
        buf[n++] = c;
    } while ((c != EOF) && (c !='\x00a'));
    buf[n-1] = '\0';

    return 1;
}

double MolData::getBallRadius(int n)
{
    return  MC->getBallRadius(Num[n]);
}

unsigned long MolData::getBallColor(int n)
{
    return  MC->getBallColor(Num[n]);
}

int MolData::replaceMolecules(MolData *md)
{
    int n, m;

    if (md == 0) return 0;

    if (md->NIons <= 0) return 0;

    if (MaxNIons < md->NIons) {
        freeMem();
        allocMem(md->NIons);
    }
    NIons = md->NIons;
    for (n = 0; n < NIons; n++) {
        strcpy(Elem[n], md->Elem[n]);
        for (m = 0; m < 3; m++) R0[n][m] = md->R0[n][m];
    }
    NSticks = -1;
    rotate();
    identify();

    return 1;
}

int MolData::replaceData3D(MolData *md)
{
    if (md == 0) return 0;


    return 1;
}


