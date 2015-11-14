#ifndef __MARCHINGCUBE_H
#define __MARCHINGCUBE_H

void MakeTriCountTable();
void CubeIndex(double *data, unsigned char *cubeindex, int nx, int ny, int nz, double val);
int TriCount(unsigned char *cubeindex, int nx, int ny, int nz);
void InterpolateVertex(double *pos1, double *pos2, double val1, double val2, double isoval, double *pos);
void FindVertices(double *data, unsigned char *cubeindex, int i, int j, int k, int nx, int ny, int nz, 
		  double xorg, double yorg, double zorg, double delx, double dely, double delz, double isoval);
void MakeTris(double *data, unsigned char *cubeindex, int nx, int ny, int nz, double xorg, double yorg, double zorg, 
	      double delx, double dely, double delz, double isoval, double *tris, double *nvec);
void MakeTris2(double *data, unsigned char *cubeindex, int nx, int ny, int nz, 
               double orgpos[3], double bv[3][3], 
	       double isoval, double *tris, double *nvec);

#endif
