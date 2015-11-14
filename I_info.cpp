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
#include "I_info.h"


I_info::I_info(const char *fn, GLConf *gc, MolConf *mc) : MolData(gc, mc)
{
    NIons = -1;
    ExistOX = 0;
    strcpy(FileName, fn);
    //readI_info("I_info");
    readI_info(FileName);
    identify();
}


I_info::~I_info()
{
}

void I_info::readI_info(char *fn)
{
    int nions = readIons(fn);
    ExistOX = (nions > 1) ? 1 : 0; 
}

int  I_info::countIons(char *fn)
{
    char str[1024], elem[5]; 
    int readdataox, res, count;
    double t, m, q, x, y, z;
    QFile f(fn);

    if (!f.exists()) return -1;   
    if (!f.open(QIODevice::ReadOnly)) return 0;
    if (f.readLine(str, 1000) < 2) {
        f.close();
        return 0;
    }
    if (sscanf(str, "%le", &t) < 1) {
        f.close();
        return 0;
    }

    count = 0;
    do {
        readdataox = 0;
        if (f.readLine(str, 1000) > 15) {
            res = sscanf(str, "%4c %le %le %le %le %le", 
                              elem, &m, &q, &x, &y, &z);
            if (res == 6) {
                if ((elem[0] == '\"') && (elem[3] == '\"')) {
                    readdataox = 1;
                    count++;
                }
            }
        }
    } while (readdataox);

    f.close();
    return count;
}

int  I_info::readIons(char *fn)
{
    int nions = countIons(fn);
    char str[1024], elem[5]; 
    int  n;
    double mass, q, md_t;
    
    if (nions < 1) return nions;
    allocMem(nions);

    QFile f(fn);

    f.open(QIODevice::ReadOnly);
    f.readLine(str, 1000);
    sscanf(str, "%le", &md_t);

    for (n = 0; n < nions; n++) {
        f.readLine(str, 1000);
        sscanf(str, "%4c %le %le %le %le %le", 
               elem, &mass, &q, R0[n], R0[n]+1, R0[n]+2);
        R0[n][0] = R0[n][0]*0.529177;
        R0[n][1] = R0[n][1]*0.529177;;
        R0[n][2] = R0[n][2]*0.529177;;
        Elem[n][0] = elem[1];
        Elem[n][1] = elem[2];
        Elem[n][2] = '\0';
        if (Elem[n][1] == ' ') Elem[n][1] = '\0';
    } 

    f.close();
    NIons = nions;

    rotate();
    return nions;
}


