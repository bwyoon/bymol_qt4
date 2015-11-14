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
#include <math.h>
#include <QFile>
#include <QDir>
#include <QTextStream>
#include "GLConf.h"

GLConf::GLConf()
{
    setDefaultGLConf();

    QString path = QDir::homePath()+"/.bymol_GLConf";
    QFile f(path);
    char str[1024];
    if (f.exists()) {
        f.open(QIODevice::ReadOnly);
        if (f.readLine(str, 1000) > 10) {
            QFile f2(str);
            if (f2.exists()) loadGLConfFile(str);
        }
        f.close(); 
    }
}

GLConf::~GLConf()
{
    QString path = QDir::homePath()+"/.bymol_GLConf";
    QFile f(path);

    f.open(QIODevice::WriteOnly); 

    QTextStream stream(&f);
    stream << GLConfFilePath; 

    f.close();
}

void GLConf::setDefaultGLConf()
{
    strcpy(GLConfFilePath, "");

    XMin = YMin = ZMin = -10.0;
    XMax = YMax = ZMax = +10.0;
    EyePos[0] = EyePos[1] = 0.0f;
    EyePos[2] = 10000.0f;
    LookAtPos[0] = LookAtPos[1] = LookAtPos[2] = 0.0f;
    UpDir[0] = UpDir[2] = 0.0f;
    UpDir[1] = 1.0f;
#ifdef __FOR_BIG_SYSTEM
    VAngle = 2.0f;
#else
    VAngle = 0.3f;
#endif
    ARatio = 1.0f;
    ZNear = 9800.0f;
    ZFar  = 10200.0f;
    VWidth = VHeight = 1920;
    VX0 = VY0 = 0;
    BGColor[0] = BGColor[1] = BGColor[2] = BGColor[3] = 1.0f;
    NLights = 1;

    for (int n = 0; n < 10; n++) LightPos[n][3] = 1.0f;
    LightPos[0][0] = 0.0f;
    LightPos[0][1] = 0.0f;
    LightPos[0][2] = 10000.0f;
    LightPos[0][3] = 1.0f;
    LightDiffuseColor[0][0] = 1.0f;
    LightDiffuseColor[0][1] = 1.0f;
    LightDiffuseColor[0][2] = 1.0f;
    LightDiffuseColor[0][3] = 1.0f;
    LightAmbientColor[0][0] = 0.f;
    LightAmbientColor[0][1] = 0.f;
    LightAmbientColor[0][2] = 0.f;
    LightAmbientColor[0][3] = 1.f;
    LightSpecularColor[0][0] = 1.0f;
    LightSpecularColor[0][1] = 1.0f;
    LightSpecularColor[0][2] = 1.0f;
    LightSpecularColor[0][3] = 1.0f;

    Shininess = 128.0f;

    RM[0][0] = RM[1][1] = RM[2][2] = 1.0;
    RM[0][1] = RM[0][2] = RM[1][0] = RM[1][2] = RM[2][0] = RM[2][1] = 0.0;

#ifdef __FOR_BIG_SYSTEM
    NQuality = 8;
#else
    NQuality = 15;
#endif

    BallRadiusFactor = 0.8;
    StickLengthFactor = 2.5;
    StickRadius = 0.20;

    DrawStickOX = 1;
    DrawIsosurfaceOX = 1;

    AntiAliasOX = 0;

    IsosurfaceSumMode = 0;
    IsosurfaceCutoff = 0.9;
    IsosurfaceColor[0] = 0x4080ff80;
    IsosurfaceColor[1] = 0xff408080;

}

void GLConf::loadGLConfFile(char *fn)
{
    setDefaultGLConf();
    char str[1024];
    int n, m, ok = 0;
    //double xmin, ymin, zmin, xmax, ymax, zmax;
    GLfloat eyepos[3];
    GLfloat lookatpos[3];
    GLfloat updir[3];
    GLfloat vangle, aratio, znear, zfar;
    GLsizei  vwidth, vheight, vx0, vy0;
    unsigned int  rgba1, rgba2, rgba3;
    GLfloat  bgcolor[4];
    GLfloat  shininess;
    int nlights;
    GLfloat lpos[10][3];
    GLfloat ldcolor[10][4];
    GLfloat lacolor[10][4];
    GLfloat lscolor[10][4];
    double rm[3][3];
    int rmox = 0;
    int ncount;

    QFile f(fn);
    if (f.exists()) {
        f.open(QIODevice::ReadOnly);
        if (f.readLine(str, 1000) < 5) {
            f.close();
            return;
        }
        if (sscanf(str, "%e%e%e", eyepos, eyepos+1, eyepos+2) < 3) {
           f.close();
           return;
        }
        if (f.readLine(str, 1000) < 5) {
            f.close();
            return;
        }
        if (sscanf(str, "%e%e%e", lookatpos, lookatpos+1, lookatpos+2) < 3) {
           f.close();
           return;
        }
        if (f.readLine(str, 1000) < 5) {
            f.close();
            return;
        }
        if (sscanf(str, "%e%e%e", updir, updir+1, updir+2) < 3) {
           f.close();
           return;
        }
        if (f.readLine(str, 1000) < 5) {
            f.close();
            return;
        }
        if (sscanf(str, "%e%e%e", &vangle, &znear, &zfar) < 3) {
           f.close();
           return;
        }
        if (f.readLine(str, 1000) < 3) {
            f.close();
            return;
        }
        if ((ncount = sscanf(str, "%d%d", &vwidth, &vheight, &vx0, &vy0)) < 2) {
           f.close();
           return;
        } else {
            if (ncount < 4) vx0 = vy0 = 0;
        }
        if (f.readLine(str, 1000) < 8) {
            f.close();
            return;
        }
        if (sscanf(str, "%x", &rgba1) < 1) {
           f.close();
           return;
        }
       	bgcolor[0] = (float)(rgba1 & 0xff000000)/(float)0xff000000;
	bgcolor[1] = (float)(rgba1 & 0x00ff0000)/(float)0x00ff0000;
	bgcolor[2] = (float)(rgba1 & 0x0000ff00)/(float)0x0000ff00;
	bgcolor[3] = (float)(rgba1 & 0x000000ff)/(float)0x000000ff;

        if (f.readLine(str, 1000) < 1) {
            f.close();
            return;
        }
        if (sscanf(str, "%e", &shininess) < 1) {
           f.close();
           return;
        }
        if (f.readLine(str, 1000) < 1) {
            f.close();
            return;
        }
        if (sscanf(str, "%d", &nlights) < 1) {
           f.close();
           return;
        }
        for (n = 0; n < nlights; n++) {
            if (f.readLine(str, 1000) < 30) {
                f.close();
                return;
            }
            if (sscanf(str, "%e%e%e%x%x%x", lpos[n], lpos[n]+1, lpos[n]+2,
                                            &rgba1, &rgba2, &rgba3) < 6) {
               f.close();
               return;
            }
       	    ldcolor[n][0] = (float)(rgba1 & 0xff000000)/(float)0xff000000;
	    ldcolor[n][1] = (float)(rgba1 & 0x00ff0000)/(float)0x00ff0000;
	    ldcolor[n][2] = (float)(rgba1 & 0x0000ff00)/(float)0x0000ff00;
	    ldcolor[n][3] = (float)(rgba1 & 0x000000ff)/(float)0x000000ff;
       	    lacolor[n][0] = (float)(rgba2 & 0xff000000)/(float)0xff000000;
	    lacolor[n][1] = (float)(rgba2 & 0x00ff0000)/(float)0x00ff0000;
	    lacolor[n][2] = (float)(rgba2 & 0x0000ff00)/(float)0x0000ff00;
	    lacolor[n][3] = (float)(rgba2 & 0x000000ff)/(float)0x000000ff;
       	    lscolor[n][0] = (float)(rgba3 & 0xff000000)/(float)0xff000000;
	    lscolor[n][1] = (float)(rgba3 & 0x00ff0000)/(float)0x00ff0000;
	    lscolor[n][2] = (float)(rgba3 & 0x0000ff00)/(float)0x0000ff00;
	    lscolor[n][3] = (float)(rgba3 & 0x000000ff)/(float)0x000000ff;
        }
        if (f.readLine(str, 1000) > 4) {
            sscanf(str, "%le%le%le", &(rm[0][0]), &(rm[1][0]), &(rm[2][0])); 
            if (f.readLine(str, 1000) > 4) {
                sscanf(str, "%le%le%le", &(rm[0][1]), &(rm[1][1]), &(rm[2][1])); 
                if (f.readLine(str, 1000) > 4) {
                   sscanf(str, "%le%le%le", &(rm[0][2]), &(rm[1][2]), &(rm[2][2])); 
                   rmox = 1;
                }
            }
        }
        ok = 1;
        f.close();
    }

    if (ok) {
        EyePos[0]=eyepos[0]; LookAtPos[0]=lookatpos[0]; UpDir[0]=updir[0]; 
        EyePos[1]=eyepos[1]; LookAtPos[1]=lookatpos[1]; UpDir[1]=updir[1]; 
        EyePos[2]=eyepos[2]; LookAtPos[2]=lookatpos[2]; UpDir[2]=updir[2]; 
        VAngle = vangle; ZNear = znear; ZFar = zfar;
        VWidth = vwidth; VHeight = vheight;
        VX0 = vx0; VY0 = vy0;
        BGColor[0] = bgcolor[0]; BGColor[1] = bgcolor[1]; 
        BGColor[2] = bgcolor[2]; BGColor[3] = bgcolor[3];
        Shininess = shininess;
        NLights = nlights;
        for (n = 0; n < NLights; n++) {
            LightPos[n][0] = lpos[n][0]; 
            LightPos[n][1] = lpos[n][1]; 
            LightPos[n][2] = lpos[n][2];
            LightDiffuseColor[n][0]  = ldcolor[n][0]; 
            LightDiffuseColor[n][1]  = ldcolor[n][1];
            LightDiffuseColor[n][2]  = ldcolor[n][2]; 
            LightDiffuseColor[n][3]  = ldcolor[n][3];
            LightAmbientColor[n][0]  = lacolor[n][0]; 
            LightAmbientColor[n][1]  = lacolor[n][1];
            LightAmbientColor[n][2]  = lacolor[n][2]; 
            LightAmbientColor[n][3]  = lacolor[n][3];
            LightSpecularColor[n][0] = lscolor[n][0]; 
            LightSpecularColor[n][1] = lscolor[n][1];
            LightSpecularColor[n][2] = lscolor[n][2]; 
            LightSpecularColor[n][3] = lscolor[n][3];
        }
        if (rmox) {
            for (n = 0; n < 3; n++)
            for (m = 0; m < 3; m++) RM[n][m] = rm[n][m];
        }
        strcpy(GLConfFilePath, fn);
    }
}

void GLConf::multiplyRMatrix(double rm[3][3])
{
    double rm0[3][3];
    int k, l, n;

    for (k = 0; k < 3; k++) {
        for (l = 0; l < 3; l++) {
            rm0[k][l] = RM[k][l];
        }
    }

    for (k = 0; k < 3; k++) {
        for (l = 0; l < 3; l++) {
            RM[k][l] = 0.0;
            for (n = 0; n < 3; n++) {
                RM[k][l] += rm[k][n]*rm0[n][l];
            }
        }
    }
}

void GLConf::rotateX(double angle)
{
    double rm[3][3];
    double ar = angle/180.0*3.14159265358979;

    rm[0][0] = 1.0;
    rm[0][1] = rm[0][2] = rm[1][0] = rm[2][0] = 0.0;

    rm[1][1] = rm[2][2] = cos(ar);
    rm[1][2] = sin(ar);
    rm[2][1] = -rm[1][2];

    multiplyRMatrix(rm);
}

void GLConf::rotateY(double angle)
{
    double rm[3][3];
    double ar = angle/180.0*3.14159265358979;

    rm[1][1] = 1.0;
    rm[1][2] = rm[1][0] = rm[2][1] = rm[0][1] = 0.0;

    rm[2][2] = rm[0][0] = cos(ar);
    rm[2][0] = sin(ar);
    rm[0][2] = -rm[2][0];

    multiplyRMatrix(rm);
}

void GLConf::rotateZ(double angle)
{
    double rm[3][3];
    double ar = angle/180.0*3.14159265358979;

    rm[2][2] = 1.0;
    rm[2][0] = rm[2][1] = rm[0][2] = rm[1][2] = 0.0;

    rm[0][0] = rm[1][1] = cos(ar);
    rm[0][1] = sin(ar);
    rm[1][0] = -rm[0][1];

    multiplyRMatrix(rm);
}

void GLConf::unrotate()
{
    RM[0][0] = RM[1][1] = RM[2][2] = 1.0;
    RM[0][1] = RM[0][2] = RM[1][0] = RM[1][2] = RM[2][0] = RM[2][1] = 0.0;
}

void GLConf::zoomIn(double f)
{
    int n;
    float dr[3], z0, dz1, dz2;

    z0 = 0.0f; 
    for (n = 0; n < 3; n++) {
        dr[n] = EyePos[n]-LookAtPos[n];
        z0 += dr[n]*dr[n]; 
    }
    z0 = (float)sqrt((double)z0);
    dz1 = z0-ZNear;
    dz2 = ZFar-z0; 
    for (n = 0; n < 3; n++) {
        dr[n] /= (float)f;
        EyePos[n] = dr[n]+LookAtPos[n];
        
    }
    z0 /= (float)f;
    ZNear = z0-dz1;
    ZFar  = z0+dz2;
}

void GLConf::zoomOut(double f)
{
    int n;
    float dr[3], z0, dz1, dz2;

    z0 = 0.0f; 
    for (n = 0; n < 3; n++) {
        dr[n] = EyePos[n]-LookAtPos[n];
        z0 += dr[n]*dr[n]; 
    }
    z0 = (float)sqrt((double)z0);
    dz1 = z0-ZNear;
    dz2 = ZFar-z0; 
    for (n = 0; n < 3; n++) {
        dr[n] *= (float)f;
        EyePos[n] = dr[n]+LookAtPos[n];
        
    }
    z0 *= (float)f;
    ZNear = z0-dz1;
    ZFar  = z0+dz2;
}

void GLConf::moveViewportUp(int v)
{
    VY0 += v;
}

void GLConf::moveViewportDown(int v)
{
    VY0 -= v;
}

void GLConf::moveViewportLeft(int v)
{
    VX0 -= v;
}

void GLConf::moveViewportRight(int v)
{
    VX0 += v;
}

void GLConf::SaveGLConfFile(char *fn)
{
    FILE *f;

    f = fopen(fn, "wt");
    if (f == NULL) return ;

    fprintf(f, "%10g %10g %10g  // Eye (Camera) Position\n", 
               EyePos[0], EyePos[1], EyePos[2]);
    fprintf(f, "%10g %10g %10g  // LookAt Position\n", 
               LookAtPos[0], LookAtPos[1], LookAtPos[2]);
    fprintf(f, "%10g %10g %10g  // Up direction\n", 
               UpDir[0], UpDir[1], UpDir[2]);
    fprintf(f, "%10g %10g %10g  // View Angle, Z-near, Z-far\n", 
               VAngle, ZNear, ZFar);
    fprintf(f, "%5d %5d %5d %d  // Viewport Width, Height, X0, Y0\n", 
               VWidth, VHeight, VX0, VY0);

    unsigned int rgb;
    rgb  = (unsigned int)(BGColor[0]*(float)255.0)*0x01000000;
    rgb += (unsigned int)(BGColor[1]*(float)255.0)*0x00010000;
    rgb += (unsigned int)(BGColor[2]*(float)255.0)*0x00000100;
    rgb += (unsigned int)(BGColor[3]*(float)255.0)*0x00000001;
    fprintf(f, "%11X  // Background Color\n", rgb);

    fprintf(f, "%11g  // Shininess\n", Shininess);

    fprintf(f, "%11d  // Number of Lights (limited to 10)\n", 
               NLights);
     
    int n, m;

    for (n = 0; n < NLights; n++) {
        fprintf(f, "%g %g %g ", 
                   LightPos[n][0], LightPos[n][1], LightPos[n][2]);
        rgb  = (unsigned int)(LightDiffuseColor[n][0]*(float)255.0)*0x01000000;
        rgb += (unsigned int)(LightDiffuseColor[n][1]*(float)255.0)*0x00010000;
        rgb += (unsigned int)(LightDiffuseColor[n][2]*(float)255.0)*0x00000100;
        rgb += (unsigned int)(LightDiffuseColor[n][3]*(float)255.0)*0x00000001;
        fprintf(f, "%08X ", rgb);
        rgb  = (unsigned int)(LightAmbientColor[n][0]*(float)255.0)*0x01000000;
        rgb += (unsigned int)(LightAmbientColor[n][1]*(float)255.0)*0x00010000;
        rgb += (unsigned int)(LightAmbientColor[n][2]*(float)255.0)*0x00000100;
        rgb += (unsigned int)(LightAmbientColor[n][3]*(float)255.0)*0x00000001;
        fprintf(f, "%08X ", rgb);
        rgb  = (unsigned int)(LightSpecularColor[n][0]*(float)255.0)*0x01000000;
        rgb += (unsigned int)(LightSpecularColor[n][1]*(float)255.0)*0x00010000;
        rgb += (unsigned int)(LightSpecularColor[n][2]*(float)255.0)*0x00000100;
        rgb += (unsigned int)(LightSpecularColor[n][3]*(float)255.0)*0x00000001;
        fprintf(f, "%08X ", rgb);
        fprintf(f, " // position, Diffuse, Ambient, Specular Color\n");
    }

    fprintf(f, "%15g %15g %15g  // a11 a21 a31\n", RM[0][0], RM[1][0], RM[2][0]);
    fprintf(f, "%15g %15g %15g  // a12 a22 a32\n", RM[0][1], RM[1][1], RM[2][1]);
    fprintf(f, "%15g %15g %15g  // a13 a23 a33\n", RM[0][2], RM[1][2], RM[2][2]);

    fclose(f);
}
