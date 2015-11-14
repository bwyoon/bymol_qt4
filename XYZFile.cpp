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
#include "XYZFile.h"

XYZFile::XYZFile(const char *fn, GLConf *gc, MolConf *mc) : MolData(gc, mc)
{
    NIons = -1;
    strcpy(FileName, fn);
    readXYZFile(FileName);
    identify();
}

void XYZFile::readXYZFile(char *fni)
{
    QFile f(fni);
    char str[1024], elem[512];
    int nions, n;
    double x, y, z;

    if (!f.exists()) return;
    if (!f.open(QIODevice::ReadOnly)) return;
    if (f.readLine(str, 1000) < 1) {
        f.close();
        return;
    }
    //QMessageBox::about(this, "", str);

    sscanf(str, "%d", &nions);
    if (nions <= 0) {
        f.close();
        return;
    }

    if (f.readLine(str, 1000) < 1) {
        f.close();
        return;
    }

    allocMem(nions);

    for (n = 0; n < nions; n++) {
        if (f.readLine(str, 1000) < 4) break;
        if (sscanf(str, "%s %le %le %le", elem, &x, &y, &z) < 4) break;
        //if (strlen(elem) > 2) break;
        //if (strlen(elem) == 1) strcat(elem, " ");
        strcpy(Elem[n], elem);
        R0[n][0] = x;
        R0[n][1] = y;
        R0[n][2] = z;
    }
    NIons = n;
    f.close();
    rotate();
}
