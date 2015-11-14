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
#include <QFile>
#include <QDir>
#include <QTextStream>
#include "MolConf.h"

const char MolConf::ELEMENT[][3] = { "",
 "H", "He", "Li", "Be",  "B",  "C",  "N",  "O",  "F", "Ne",
"Na", "Mg", "Al", "Si",  "P",  "S", "Cl", "Ar",  "K", "Ca",
"Sc", "Ti", "Va", "Cr", "Mn", "Fe", "Co", "Ni", "Cu", "Zn",
"Ga", "Ge", "As", "Se", "Br", "Kr", "Rb", "Sr",  "Y", "Zr",
"Nb", "Mo", "Tc", "Ru", "Rh", "Pd", "Ag", "Cd", "In", "Sn",
"Sb", "Te",  "I", "Xe", "Cs", "Ba", "La", "Ce", "Pr", "Nd",
"Pm", "Sm", "Eu", "Gd", "Tb", "Dy", "Ho", "Er", "Tm", "Yb",
"Lu", "Hf", "Ta",  "W", "Re", "Os", "Ir", "Pt", "Au", "Hg",
};

const double MolConf::CVRADIUS[] = {0.25,
        0.31, 0.32, 1.28, 0.96, 0.84, 0.76, 0.71, 0.66, 0.57, 0.58,
        1.66, 1.15 /*1.41*/, 1.21, 1.11, 1.07, 1.05, 1.02, 1.06, 2.03, 1.76,
        1.70, 1.60, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.24, 1.32,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.46, 1.42, 1.39, 1.45, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.36, 1.36, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
    };

const unsigned int MolConf::COLOR[] = { 0xaaaaaaff,
0x0000ffff, 0xaaaaaaff, 0xaaaaaaff, 0xaaaaaaff, 0xaaaaaaff,
0x606060ff, 0x0080ffff, 0xff0000ff, 0xaaaaaaff, 0xaaaaaaff,
0xaaaaaaff, 0x008000ff, 0xaaaaaaff, 0xaaaaaaff, 0xaaaaaaff,
0xffff00ff, 0xaaaaaaff, 0xaaaaaaff, 0xaaaaaaff, 0xaaaaaaff,
0xaaaaaaff, 0xaaaaaaff, 0xaaaaaaff, 0xaaaaaaff, 0xaaaaaaff,
0xaaaaaaff, 0xaaaaaaff, 0xaaaaaaff, 0xaaaaaaff, 0xaaaaaaff,
0xaaaaaaff, 0xaaaaaaff, 0xaaaaaaff, 0xaaaaaaff, 0xaaaaaaff,
0xaaaaaaff, 0xaaaaaaff, 0xaaaaaaff, 0xaaaaaaff, 0xaaaaaaff,
0xaaaaaaff, 0xaaaaaaff, 0xaaaaaaff, 0x77aa77ff, 0x8080ffff,
0x3333aaff, 0xaaaaaaff, 0xaaaaaaff, 0xaaaaaaff, 0xaaaaaaff,
0xaaaaaaff, 0xaaaaaaff, 0xaaaaaaff, 0xaaaaaaff, 0xaaaaaaff,
0xaaaaaaff, 0xaaaaaaff, 0xaaaaaaff, 0xaaaaaaff, 0xaaaaaaff,
0xaaaaaaff, 0xaaaaaaff, 0xaaaaaaff, 0xaaaaaaff, 0xaaaaaaff,
0xaaaaaaff, 0xaaaaaaff, 0xaaaaaaff, 0xaaaaaaff, 0xaaaaaaff,
0xaaaaaaff, 0xaaaaaaff, 0xaaaaaaff, 0xaaaaaaff, 0xaaaaaaff,
0xaaaaaaff, 0xaaaaaaff, 0xaaaaaaff, 0xffbb00ff, 0xaaaaaaff,
};

MolConf::MolConf()
{
    setDefaultMolConf();

    QString path = QDir::homePath()+"/.bymol_MolConf";
    QFile f(path);
    char str[1024];
    if (f.exists()) {
        f.open(QIODevice::ReadOnly);
        if (f.readLine(str, 1000) > 10) {
            QFile f2(str);
            if (f2.exists()) loadMolConfFile(str);
        }
        f.close();
    }

}

MolConf::~MolConf()
{
    QString path = QDir::homePath()+"/.bymol_MolConf";
    QFile f(path);

    f.open(QIODevice::WriteOnly);

    QTextStream stream(&f);
    stream << MolConfFilePath;

    f.close();
}

void MolConf::setDefaultMolConf()
{
    strcpy(MolConfFilePath,"");

    MolConfFileOX     = 0;
    BallRadiusFactor  = 1.0;
    StickLengthFactor = 1.0;
    MaxStickLength    = 5.5;

    IsosurfaceSumMode = 0;
    IsosurfaceCutoff = 0.9;
    IsosurfaceColor[0] = 0x0088ff80;
    IsosurfaceColor[1] = 0xff008880;

}

void MolConf::loadMolConfFile(char *fn)
{
    int ok = 0;
    char str[1024];
    int nions, nsticks, nisos, n1, n2, n, m;

    char elem[MAX_ELEMENTS][6];
    int     z[MAX_ELEMENTS];
    double br[MAX_ELEMENTS];
    unsigned int bc[MAX_ELEMENTS];

    char epair[2][6];
    double sl, st;
    double    slength[MAX_ELEMENTS][MAX_ELEMENTS];
    double sthickness[MAX_ELEMENTS][MAX_ELEMENTS];
    QFile f(fn);

    if (f.exists()) {
        f.open(QIODevice::ReadOnly);

        // Read ball data
        if (f.readLine(str, 1000) < 1) goto STOP;
        if (sscanf(str, "%d", &nions) < 1) goto STOP;
        strcpy(elem[0], " ");
        z[0]  = 1;
        br[0] = 0.25;
        bc[0] = 0x808080ff;
        for (n = 1; n <= nions; n++) {
            if (f.readLine(str, 1000) < 12) goto STOP;
            if (sscanf(str, "%s%d%le%x", elem[n], z+n, br+n, bc+n) < 4) 
                goto STOP;
        }

        // Read stick data
        if (f.readLine(str, 1000) < 1) goto STOP; 
        if (sscanf(str, "%d", &nsticks) < 1) goto STOP;
        for (n = 0; n <= nions; n++) {
            for (m = 0; m <= nions; m++) {
                slength[n][m]    = 0.5;
                sthickness[n][m] = 0.15;
            }
        }
        MaxStickLength = 0.5;
        for (n = 0; n < nsticks; n++) {
            if (f.readLine(str, 1000) < 7) goto STOP;
            if (sscanf(str, "%s%s%le%le", epair[0], epair[1], &sl, &st) < 4) 
                goto STOP;

            n1 = n2 = 0;
            for (m = 1; m <= nions; m++) {
                if (strcmp(epair[0], elem[m]) == 0) {
                    n1 = m;
                    break;
                }
            }
            for (m = 1; m <= nions; m++) {
                if (strcmp(epair[1], elem[m]) == 0) {
                    n2 = m;
                    break;
                }
            }
            if ((n1 > 0) && (n2 > 0)) {
                slength[n1][n2] = slength[n2][n1] = sl;
                sthickness[n1][n2] = sthickness[n2][n1] = st;
                if (MaxStickLength < sl) MaxStickLength = sl;
                //printf("MaxStickLength (%d, %d) = %f\n", n1, n2, slength[n1][n2]);
            }
        }

        if (f.readLine(str, 1000) > 0)  {
            if (sscanf(str, "%d", &nisos) > 0) {
                for (n = 0; n < nisos; n++) {
                    f.readLine(str, 1000);
                    sscanf(str, "%x", IsosurfaceColor+n);
                }
            }
        }
        ok = 1;

        f.close();
    }

    if (ok) {
        MolConfFileOX = 1;
        BallRadiusFactor = 1.0;
        StickLengthFactor = 1.0;

        NElements = nions;
        for (n = 0; n <= nions; n++) {
            strcpy(Element[n], elem[n]);
            Z[n] = z[n];
            BallRadius[n] = br[n];
            BallColor[n]  = bc[n];
        }
        for (n = 0; n <= nions; n++) {
            for (m = 0; m <= nions; m++) {
                StickLength[n][m] = slength[n][m];
                StickThickness[n][m] = sthickness[n][m];
                //printf("(%d,%d) = %f\n", n, m, slength[n][m]);
            }
        }
        strcpy(MolConfFilePath, fn);
    }

    return;

STOP: f.close();
}


int MolConf::identifyIon(char *elem, int previon)
{
    int m, ion;

    if (!MolConfFileOX) {
        if (previon > 0) {
            if (strcmp(elem, ELEMENT[previon]) == 0) {
                ion  = previon;
            } else {
                previon = 0;
            }
        }
        if (previon == 0) {
            for (m = 1; m <= 100; m++) {
                if (strcmp(elem, ELEMENT[m]) == 0) break;
            }
            
            ion = (m > 100) ? 0 : m;
        }
    } else {
        if (previon > 0) {
            if (strcmp(elem, Element[previon]) == 0) {
                ion  = previon;
            } else {
                previon = 0;
            }
        }
        if (previon == 0) {
            for (m = 1; m <= NElements; m++) {
                if (strcmp(elem, Element[m]) == 0) break;
            }
            ion = (m > NElements) ? 0 : m;
        }


    }
    return ion;
}

int MolConf::getAtomicNumber(int num) 
{
    return (MolConfFileOX) ? Z[num] : num; 
}

char * MolConf::getElementName(int num) 
{
    return (MolConfFileOX) ? Element[num] : (char *)ELEMENT[num]; 
}

double MolConf::getBallRadius(int num)
{
    return (MolConfFileOX) ? BallRadius[num] 
                           : 0.8*MolConf::CVRADIUS[num];
}

unsigned long MolConf::getBallColor(int num)
{
    return (MolConfFileOX) ? BallColor[num] : MolConf::COLOR[num];
}

int MolConf::checkStickLength(int num1, int num2, double r)
{
    double r2;

    if (!MolConfFileOX) {
        r2 = StickLengthFactor*2.5*sqrt(CVRADIUS[num1]*CVRADIUS[num2]);
    } else {
        r2 = StickLengthFactor*StickLength[num1][num2];
    }

    return (r <= r2);
} 

double MolConf::GetStickLength(int num1, int num2)
{
    double r2;

    if (!MolConfFileOX) {
        r2 = StickLengthFactor*2.5*sqrt(CVRADIUS[num1]*CVRADIUS[num2]);
    } else {
        r2 = StickLengthFactor*StickLength[num1][num2];
    }

    return r2;
} 

double MolConf::getStickRadius(int num1, int num2)
{
    double r;

    if (!MolConfFileOX) {
        r = 0.25;      
    } else {
        r = StickThickness[num1][num2];
    }

    return r;
}
