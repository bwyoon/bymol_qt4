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

#ifndef __GLCONF_H
#define __GLCONF_H

#include <QtOpenGL>

typedef GLfloat GLfloat3[3];
typedef GLfloat GLfloat4[4];

class GLConf
{
public :
    ~GLConf();

    char GLConfFilePath[512];
    double XMin, XMax, YMin, YMax, ZMin, ZMax;
    double RM[3][3];
    GLfloat  EyePos[3];
    GLfloat  LookAtPos[3]; 
    GLfloat  UpDir[3];
    GLfloat VAngle, ARatio, ZNear, ZFar; 
    GLsizei  VWidth, VHeight, VX0, VY0;
    GLfloat  BGColor[4];
    GLfloat Shininess;

    //GLfloat3 *LightPos;
    //GLfloat4 *LightDiffuseColor;
    //GLfloat4 *LightAmbientColor;
    //GLfloat4 *LightSpecularColor;

    int NLights;
    GLfloat LightPos[10][4];
    GLfloat LightDiffuseColor[10][4];
    GLfloat LightAmbientColor[10][4];
    GLfloat LightSpecularColor[10][4];

    

    int NQuality;
    int AntiAliasOX;
    int DrawStickOX;
    int DrawIsosurfaceOX;

    double BallRadiusFactor;
    double StickLengthFactor;
    double StickRadius;

    unsigned long IsosurfaceColor[10];
    int IsosurfaceSumMode;
    double IsosurfaceCutoff;

    GLConf();

    void setDefaultGLConf();
    void loadGLConfFile(char *);

    void unrotate();
    void multiplyRMatrix(double rm[3][3]);
    void rotateX(double);
    void rotateY(double);
    void rotateZ(double);
    void zoomIn(double);
    void zoomOut(double);

    void moveViewportUp(int);
    void moveViewportDown(int);
    void moveViewportLeft(int);
    void moveViewportRight(int);

    void SaveGLConfFile(char *);
};

#endif
