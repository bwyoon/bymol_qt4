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
#include "CubeFile.h"

CubeFile::CubeFile(const char *fn, GLConf *gc, MolConf *mc) : MolData(gc, mc)
{
    NIons = -1;
    strcpy(FileName, fn);
    readCubeFile(FileName);
    identify();
}

int ReadLn(FILE *f, char *str)
{
    int c, n = 0;

    if (f == NULL) return 0;
    do {
        c = fgetc(f);
        str[n++] = c;
    } while ((c != EOF) && (c !='\x00a'));
    str[n-1] = '\0';
    return 1;
}

void CubeFile::readCubeFile(char *fni)
{
    FILE *fi;
    int n, count;
    double mass;
    double x, maxabs, sumabs, sumsqrs;
    char str[2048];
    // QFile qf("I_info");
    //QMessageBox::about(0, "drop file", QFileInfo(fni).dirPath());

    int iinfoox = (QFile(QFileInfo(fni).dir().path()+"/I_info").exists()) ? 1 : 0;
    //int iinfoox = 0;

    fi = fopen(fni, "rt");
    if (fi == NULL) {
        return;
    }

    ReadLn(fi, str);
    count = sscanf(str, "%d %le %le %le", 
                       &NIons, OrgData3D+0, OrgData3D+1, OrgData3D+2); 
    if (count != 4) {
        ReadLn(fi, str);
        ReadLn(fi, str);
        count = sscanf(str, "%d %le %le %le",
                           &NIons, OrgData3D+0, OrgData3D+1, OrgData3D+2);
    }
    
    //fscanf(fi, "%d %le %le %le", &NIons, OrgData3D+0, OrgData3D+1, OrgData3D+2);
    fscanf(fi, "%d %le %le %le", NData3D+0, 
           &(MatData3D[0][0]), &(MatData3D[0][1]), &(MatData3D[0][2]));
    fscanf(fi, "%d %le %le %le", NData3D+1, 
           &(MatData3D[1][0]), &(MatData3D[1][1]), &(MatData3D[1][2]));
    fscanf(fi, "%d %le %le %le", NData3D+2, 
           &(MatData3D[2][0]), &(MatData3D[2][1]), &(MatData3D[2][2]));

    if (iinfoox) {
    }
    

    allocMem(NIons);
    Data3D = new double[NData3D[0]*NData3D[1]*NData3D[2]];
    CubeIndex = new unsigned char[NData3D[0]*NData3D[1]*NData3D[2]];
    Data3DOX = 1;

    for (n = 0; n < NIons; n++) {
        fscanf(fi, "%d %le %le %le %le", Num+n, &mass, 
                    &(R0[n][0]), &(R0[n][1]), &(R0[n][2]));
        strcpy(Elem[n], MolConf::ELEMENT[Num[n]]);
        //sprintf(str, "%d %le %le %le %le", 
        //        Z[n], mass, R0[n][0],R0[n][1],R0[n][2]);
    }

    if (iinfoox) {
        OrgData3D[0] *= 0.529177;
        OrgData3D[1] *= 0.529177;
        OrgData3D[2] *= 0.529177;
        MatData3D[0][0] *= 0.529177;
        MatData3D[0][1] *= 0.529177;
        MatData3D[0][2] *= 0.529177;
        MatData3D[1][0] *= 0.529177;
        MatData3D[1][1] *= 0.529177;
        MatData3D[1][2] *= 0.529177;
        MatData3D[2][0] *= 0.529177;
        MatData3D[2][1] *= 0.529177;
        MatData3D[2][2] *= 0.529177;
        for (n = 0; n < NIons; n++) {
            R0[n][0] = R0[n][0]*0.529177;
            R0[n][1] = R0[n][1]*0.529177;
            R0[n][2] = R0[n][2]*0.529177;
        }
    }

    maxabs = 0.0;
    sumabs = 0.0;
    sumsqrs = 0.0;
    for (n = 0; n < NData3D[0]*NData3D[1]*NData3D[2]; n++) {
        fscanf(fi, "%le", Data3D+n);
        x = (Data3D[n] < 0.0) ? -Data3D[n] : Data3D[n];
        if (maxabs < x) maxabs = x;
        sumabs += x; 
        sumsqrs += x*x;
    }
    Data3DMaxAbs = maxabs;
    Data3DSumAbs = sumabs;
    Data3DSumSqrs = sumsqrs;
    
    fclose(fi);

    rotate();
}


