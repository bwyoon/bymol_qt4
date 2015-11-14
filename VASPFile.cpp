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
#include "VASPFile.h"

POSCARFile::POSCARFile(const char *fn, GLConf *gc, MolConf *mc) 
: MolData(gc, mc)
{
    NIons = -1;
    strcpy(FileName, fn);
    readPOSCARFile(FileName);
    identify();
    //printf("NIons = %d\n", NIons);
}

void POSCARFile::calculateCellMinMax()
{
    int n, m;
    double v[3];

    for (n = 0; n < 3; n++) {
        Min[n] = +1.0E+300;
        Max[n] = -1.0E+300;
    }

    n = 0;
    while (n < 8) {
        if (n == 0) {
            for (m = 0; m < 3; m++) v[m] = 0.0;
        } else if (n < 4) {
            for (m = 0; m < 3; m++) v[m] = LVector[n-1][m]*ScalingFactor;
        } else if (n == 4) {
            for (m = 0; m < 3; m++)
                v[m] = (LVector[0][m]+LVector[1][m])*ScalingFactor;
        } else if (n == 5) {
            for (m = 0; m < 3; m++)
                v[m] = (LVector[0][m]+LVector[2][m])*ScalingFactor;
        } else if (n == 6) {
            for (m = 0; m < 3; m++)
                v[m] = (LVector[1][m]+LVector[2][m])*ScalingFactor;
        } else {
            for (m = 0; m < 3; m++)
                v[m]=(LVector[0][m]+LVector[1][m]+LVector[2][m])*ScalingFactor;
        }

        for (m = 0; m < 3; m++) {
            if (v[m] < Min[m]) Min[m] = v[m];
            if (v[m] > Max[m]) Max[m] = v[m];
        }

        n++;
    }
}


void POSCARFile::readPOSCARData(FILE *f)
{
    char str[4096];
    int count, count2, c[20];
    int nions, n, m, l, k, nn, ox;
    double pos[3];
    char pb[3][8];
    FILE *f2;

    ReadLine(f, Comments);

    ReadLine(f, str);
    ScalingFactor = atof(str);
    ReadLine(f, str);
    sscanf(str, "%le%le%le", LVector[0], LVector[0]+1, LVector[0]+2);
    ReadLine(f, str);
    sscanf(str, "%le%le%le", LVector[1], LVector[1]+1, LVector[1]+2);
    ReadLine(f, str);
    sscanf(str, "%le%le%le", LVector[2], LVector[2]+1, LVector[2]+2);

    calculateCellMinMax();

    ReadLine(f, str);
    count = sscanf(str, "%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d",
        c, c+1, c+2, c+3, c+4, c+5, c+6, c+7, c+8, c+9,
        c+10, c+11, c+12, c+13, c+14, c+15, c+16, c+17, c+18, c+19);
    if (count == 0) {
        count2 = sscanf(str, "%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s",
                 Species[0], Species[1], Species[2], Species[3],
                 Species[4], Species[5], Species[6], Species[7],
                 Species[8], Species[9], Species[10], Species[11],
                 Species[12], Species[13], Species[14], Species[15],
                 Species[16], Species[17], Species[18], Species[19]);
        if (count2 > 0) {
            NSpecies = count2;
            for (m = 0; m < count2; m++) {
                //if (strlen(Species[m]) == 1) {
                //    Species[m][2] = '\0';
                //    Species[m][1] = Species[m][0];
                //    Species[m][0] = ' ';
                //}
            }
        }
        ReadLine(f, str);
        count = sscanf(str, "%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d",
                    c, c+1, c+2, c+3, c+4, c+5, c+6, c+7, c+8, c+9,
                    c+10, c+11, c+12, c+13, c+14, c+15, c+16, c+17, c+18, c+19);
    } else {
        NSpecies = count;
        ox = 1;
        f2 = fopen("TYPENAME", "rt");
        if (f2 != NULL) {
            for (m = 0; m < NSpecies; m++) {
                if (fscanf(f2, "%s", Species[m]) != 1) {
                    ox = 0;
                    break;
                }
                //if (strlen(Species[m]) == 1) {
                //    Species[m][2] = '\0';
                //    Species[m][1] = Species[m][0];
                //    Species[m][0] = ' ';
                //}
            }
            fclose(f2);
        } else {
            ox = 0;
        }

        if (!ox) {
            for (m = 0; m < NSpecies; m++) {
                printf("Enter the name of element %d which has %d ions: ",
                       m+1, c[m]);
                scanf("%s", Species[m]);
            }
        }
    }

    nions = 0;
    for (m = 0; m < NSpecies; m++) {
        SpeciesCount[m] = c[m];
        nions += c[m];
    }

    ReadLine(f, str);
    if ((str[0] == 's') || (str[0] == 'S')) {
        SelectiveDynamicsOX = 1;
        ReadLine(f, str);
    } else {
        SelectiveDynamicsOX = 0;
    }

    CartesianOX = ((str[0] == 'c') || (str[0] == 'C')|| (str[0] == 'k')
                   || (str[0] == 'K'));
    allocMem(nions);

    nn = 0;
    for (n = 0; n < NSpecies; n++) {
        for (m = 0; m < SpeciesCount[n]; m++) {
            strcpy(Elem[nn], Species[n]);
            ReadLine(f, str);
            if (SelectiveDynamicsOX) {
                sscanf(str, "%le%le%le%s%s%s", R0[nn], R0[nn]+1, R0[nn]+2,
                           pb[0], pb[1], pb[2] );
                if (!CartesianOX) {
                    for (l = 0; l < 3; l++) pos[l] = R0[nn][l];
                    for (l = 0; l < 3; l++) {
                        R0[nn][l] = 0.0;
                        for (k = 0; k < 3; k++) {
                            R0[nn][l] += LVector[k][l]*pos[k];
                        }
                    }
                }
                for (l = 0; l < 3; l++) {
                    R0[nn][l] *= ScalingFactor;
                    R0[nn][l] -= 0.5*(Min[l]+Max[l]);
                } 
                //for (l = 0; l < 3; l++) {
                //    PosOX[nn][l] = ((pb[l][0] == 't') || (pb[l][0] == 'T'));
                //}
            } else {
                sscanf(str, "%le%le%le", pos, pos+1, pos+2);
                //for (l = 0; l < 3; l++) PosOX[nn][l] = 1;
            }
            nn++;
        }
    }

    NIons = nn;
    //printf("%d ions read.\n", nn);
    // CalculateInverseLVector();

    //return 1;

}

void POSCARFile::readPOSCARFile(char *fni)
{
    FILE *f;

    f = fopen(fni, "rt");

    readPOSCARData(f);

    fclose(f);
}
/*
void VASPFile::readVASPFile(char *fni)
{
    QFile f(fni);
    char str[1024], elem[512];
    int count, count2, nions, n, m, l;
    double x, y, z;
    double scalef, bv[3][3];
    char elem_a[20][8];
    int ic[20];
    int cartesianox, nn;
    double b01[3], b12[3], b20[3], b012[3];
    double xmin, ymin, zmin, xmax, ymax, zmax; 
    double shiftx, shifty, shiftz;
    int ox;

    if (!f.exists()) return;
    if (!f.open(QIODevice::ReadOnly)) return;

    if (f.readLine(str, 1000) < 1) { f.close(); return; }
    if (f.readLine(str, 1000) < 1) { f.close(); return; }
    sscanf(str, "%le", &scalef);

    if (f.readLine(str, 1000) < 1) { f.close(); return; }
    sscanf(str, "%le%le%le", bv[0], bv[0]+1, bv[0]+2);
    if (f.readLine(str, 1000) < 1) { f.close(); return; }
    sscanf(str, "%le%le%le", bv[1], bv[1]+1, bv[1]+2);
    if (f.readLine(str, 1000) < 1) { f.close(); return; }
    sscanf(str, "%le%le%le", bv[2], bv[2]+1, bv[2]+2);

    for (l = 0; l < 3; l++) {
        for (m = 0; m < 3; m++) {
            bv[l][m] *= scalef;
        }
    }

    xmin = ymin = zmin = +1.0E+300;
    xmax = ymax = zmax = -1.0E+300;
    for (n = 0; n < 3; n++) {
        if (xmin > bv[n][0]) xmin = bv[n][0];
        if (ymin > bv[n][1]) ymin = bv[n][1];
        if (zmin > bv[n][2]) zmin = bv[n][2];
        if (xmax < bv[n][0]) xmax = bv[n][0];
        if (ymax < bv[n][1]) ymax = bv[n][1];
        if (zmax < bv[n][2]) zmax = bv[n][2];
    }

    for (n = 0; n < 3; n++) {
        b01[n] = bv[0][n]+bv[1][n];
        b12[n] = bv[1][n]+bv[2][n];
        b20[n] = bv[2][n]+bv[0][n];
        b012[n] = bv[0][n]+bv[1][n]+bv[2][n];
    }

    if (xmin > b01[0]) xmin = b01[0];
    if (xmin > b12[0]) xmin = b12[0];
    if (xmin > b20[0]) xmin = b20[0];
    if (xmin > b012[0]) xmin = b012[0];
    if (ymin > b01[1]) xmin = b01[1];
    if (ymin > b12[1]) xmin = b12[1];
    if (ymin > b20[1]) xmin = b20[1];
    if (ymin > b012[1]) xmin = b012[1];
    if (zmin > b01[2]) xmin = b01[2];
    if (zmin > b12[2]) xmin = b12[2];
    if (zmin > b20[2]) xmin = b20[2];
    if (zmin > b012[2]) xmin = b012[2];
    if (xmax < b01[0]) xmax = b01[0];
    if (xmax < b12[0]) xmax = b12[0];
    if (xmax < b20[0]) xmax = b20[0];
    if (xmax < b012[0]) xmax = b012[0];
    if (ymax < b01[1]) xmax = b01[1];
    if (ymax < b12[1]) xmax = b12[1];
    if (ymax < b20[1]) xmax = b20[1];
    if (ymax < b012[1]) xmax = b012[1];
    if (zmax < b01[2]) xmax = b01[2];
    if (zmax < b12[2]) xmax = b12[2];
    if (zmax < b20[2]) xmax = b20[2];
    if (zmax < b012[2]) xmax = b012[2];

    shiftx = 0.5*(xmin+xmax);
    shifty = 0.5*(ymin+ymax);
    shiftz = 0.5*(zmin+zmax);

    if (f.readLine(str, 1000) < 1) { f.close(); return; }
    count = sscanf(str, "%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s",
                   elem_a[0], elem_a[1], elem_a[2], elem_a[3], elem_a[4], 
                   elem_a[5], elem_a[6], elem_a[7], elem_a[8], elem_a[9], 
                   elem_a[10], elem_a[11], elem_a[12], elem_a[13], elem_a[14], 
                   elem_a[15], elem_a[16], elem_a[17], elem_a[18], elem_a[19]); 
    if (count < 1) { f.close(); return; }
    for (m = 0; m < count; m++) {
        if (strlen(elem_a[m]) == 1) strcat(elem_a[m], " ");
    }

    if (f.readLine(str, 1000) < 1) { f.close(); return; }
    count2 = sscanf(str, "%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d",
        ic, ic+1, ic+2, ic+3, ic+4, ic+5, ic+6, ic+7, ic+8, ic+9,
        ic+10, ic+11, ic+12, ic+13, ic+14, ic+15, ic+16, ic+17, ic+18, ic+19);
    if (count != count2) { f.close(); return; }
    
    nions = 0;
    for (m = 0; m < count2; m++) {
        nions += ic[m];
    } 

    allocMem(nions);

    if (f.readLine(str, 1000) < 1) { f.close(); return; }
    if (f.readLine(str, 1000) < 1) { f.close(); return; }
    cartesianox = ((str[0] == 'c') || (str[0] == 'C'));

    ox = 1;
    nn = 0;
    for (n = 0; n < count; n++) {
        for (m = 0; m < ic[n]; m++) {
            if (f.readLine(str, 1000) < 1) ox = 0;
            if (ox) {
                sscanf(str, "%le%le%le", &x, &y, &z);
                if (cartesianox) {
                    R0[nn][0] = x-shiftx;
                    R0[nn][1] = y-shifty;
                    R0[nn][2] = z-shiftz;
                } else {
                    R0[nn][0] = bv[0][0]*x+bv[1][0]*y+bv[2][0]*z-shiftx;
                    R0[nn][1] = bv[0][1]*x+bv[1][1]*y+bv[2][1]*z-shifty;
                    R0[nn][2] = bv[0][2]*x+bv[1][2]*y+bv[2][2]*z-shiftz;
                }
                strcpy(Elem[nn], elem_a[n]);
                nn++;
            }
            if (!ox) break;
        }
        if (!ox) break;
    }

    NIons = nn;
    f.close();
    rotate();
}
*/
