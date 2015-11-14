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

#include <QApplication>
#include <QWidget>
#include <QPainter>
#include <QFileDialog> 
#include <QInputDialog> 
#include <QEvent>
#include <QFile>
#include <QGLWidget>
#include <GL/glu.h>
#include <QPixmap>
#include <QClipboard>
#include <QThread>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include "DrawWidget.h"
#include "I_info.h"
#include "CubeFile.h"
#include "XYZFile.h"
#include "VASPFile.h"

DrawWidget::DrawWidget(char *fn, QWidget *parent) //, const char *name )
        : QGLWidget( parent) //, name )
{
    setMinimumSize(800, 800);
    setWindowTitle("bymol");
    setFormat(QGLFormat(QGL::DoubleBuffer | QGL::DepthBuffer));

    moldata = 0;
    openMolDataFile(fn);
    if (moldata == 0) OpenFile();
    setAcceptDrops(true);
}

void DrawWidget::dragEnterEvent(QDragEnterEvent *event)
{
    if (event->mimeData()->hasFormat("text/uri-list"))
        event->acceptProposedAction();
}

void DrawWidget::dropEvent(QDropEvent *event)
{
    char fn[512];

    QList<QUrl> urls = event->mimeData()->urls();
    if (urls.isEmpty())  return;

    QString fileName = urls.first().toLocalFile();
    if (fileName.isEmpty()) return;

    strcpy(fn, fileName.toLocal8Bit().constData());
    openMolDataFile(fn);
    updateGL();
}


void DrawWidget::openMolDataFile(char *fn)
{
    MolData *moldata1 = 0;

    if (fn == 0) {
        if (QFile("poscar_optimized.xyz").exists()) {
            moldata1 = new XYZFile("poscar_optimized.xyz", &glconf, &molconf);
        } else if (QFile("poscar_0.xyz").exists()) {
            moldata1 = new XYZFile("poscar_0.xyz", &glconf, &molconf);
        } else if (QFile("optimized.xyz").exists()) {
            moldata1 = new XYZFile("optimized.xyz", &glconf, &molconf);
        } else if (QFile("0.xyz").exists()) {
            moldata1 = new XYZFile("0.xyz", &glconf, &molconf);
        } else if (QFile("CONTCAR").exists()) {
            moldata1 = new POSCARFile("CONTCAR", &glconf, &molconf);
        } else if (QFile("POSCAR").exists()) {
            moldata1 = new POSCARFile("POSCAR", &glconf, &molconf);
        } else if (QFile("default.xyz").exists()) {
            moldata1 = new XYZFile("default.xyz", &glconf, &molconf);
        } else if (QFile("I_info").exists()) {
            moldata1 = new I_info("I_info", &glconf, &molconf);
        }
    } else {
        char ext[256], basename[256];
        MolData::GetFileNameExtension(fn, ext);
        MolData::GetFileBaseName(fn, basename);

        if (strcmp(basename, "I_info") == 0) {
            moldata1 = new I_info(fn, &glconf, &molconf);
        } else if (strcmp(basename, "POSCAR") == 0) {
            moldata1 = new POSCARFile(fn, &glconf, &molconf);
        } else if (strcmp(basename, "CONTCAR") == 0) {
            moldata1 = new POSCARFile(fn, &glconf, &molconf);
        } else if (strcmp(ext, "cube") == 0) {
            int nit;
            double val;
            moldata1 = new CubeFile(fn, &glconf, &molconf);
            moldata1->makeIsosurfaces(&nit, &val);
        } else if (strcmp(ext, "xyz") == 0) {
            moldata1 = new XYZFile(fn, &glconf, &molconf);
        } else if (strcmp(ext, "POSCAR") == 0) {
            moldata1 = new POSCARFile(fn, &glconf, &molconf);
        } else if (strcmp(ext, "I_info") == 0) {
            moldata1 = new I_info(fn, &glconf, &molconf);
        }
    }
    if (moldata1 != 0) {
        if (moldata1->NIons > 0) {
            if (moldata != 0) delete moldata;
            moldata = moldata1;
            QString str = "bymol - ";
            str += moldata->FileName;
            setWindowTitle(str);
            parentWidget()->setWindowTitle(str);
        }
    }
}


#ifndef GL_MULTISAMPLE
#define GL_MULTISAMPLE  0x809D
#endif

void DrawWidget::initializeGL()
{
    glClearDepth(1.0f);

    glEnable( GL_DEPTH_TEST );
    glEnable( GL_CULL_FACE );
    glEnable(GL_MULTISAMPLE);
    glEnable( GL_NORMALIZE );

    glDepthFunc(GL_LESS);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	glEnable(GL_POINT_SMOOTH);
	glEnable(GL_LINE_SMOOTH );
    glEnable(GL_NORMALIZE);
}

void DrawWidget::paintGL()
{
    int n;
    //clock_t t1 = clock();

    initScene();
    if (!glconf.AntiAliasOX) {
        drawBalls();
#ifndef __NOSTICK__
        drawSticks();
#endif
        drawIsosurfaces();
            //glFlush();           

    } else {
        ///*
        int NJitter = 5;
        double XYOff[5][2] = 
        {{0.5, 0.5}, {0.3, 0.1}, {0.7, 0.9}, {0.9, 0.3}, {0.1, 0.7}};
        //*/
        /*
        int NJitter = 16;
        double XYOff[16][2] = 
        {{0.375, 0.4375}, {0.625, 0.0625}, {0.875, 0.1875}, {0.125, 0.0625},
         {0.375, 0.6875}, {0.875, 0.4375}, {0.625, 0.5625}, {0.375, 0.9375},
         {0.625, 0.3125}, {0.125, 0.5625}, {0.125, 0.8125}, {0.375, 0.1875},
         {0.875, 0.9375}, {0.875, 0.6875}, {0.125, 0.3125}, {0.625, 0.8125}};
        */
        glClear(GL_ACCUM_BUFFER_BIT);
        for (n = 0; n < NJitter; n++) {
            setFrustum(XYOff[n][0], XYOff[n][1]);
            drawBalls();
#ifndef __NOSTICK__
            drawSticks();
#endif
            drawIsosurfaces();

            //glFlush();           
            glAccum(GL_ACCUM, 1.f/(double)NJitter);
        }
        glAccum(GL_RETURN, 1.f);
    }
    //printf("time spent for drawing: %f\n", (double)(clock()-t1)/(double)CLOCKS_PER_SEC);
}

void DrawWidget::resizeGL( int width, int height )
{
    GLfloat w = (float) width / (float) height;
    GLfloat h = 1.0;

    glViewport( 0, 0, width, height );
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum( -w, w, -h, h, 5.0, 60.0 );
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef( 0.0, 0.0, -40.0 );
}

void DrawWidget::initScene()
{
    int w = width();
    int h = height();
    int n;

    glClearColor(glconf.BGColor[0], glconf.BGColor[1],
                 glconf.BGColor[2], glconf.BGColor[3]);

    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glViewport((w-glconf.VWidth)/2+glconf.VX0, (h-glconf.VHeight)/2+glconf.VY0, glconf.VWidth, glconf.VHeight);
    gluPerspective(glconf.VAngle, glconf.ARatio,glconf.ZNear, glconf.ZFar);
    glMatrixMode(GL_MODELVIEW);

    glLoadIdentity();
    gluLookAt(glconf.EyePos[0], glconf.EyePos[1], glconf.EyePos[2],
              glconf.LookAtPos[0], glconf.LookAtPos[1], glconf.LookAtPos[2],
              glconf.UpDir[0], glconf.UpDir[1], glconf.UpDir[2]);
    glShadeModel( GL_SMOOTH );

    glMaterialf(GL_FRONT, GL_SHININESS, glconf.Shininess);
    glMaterialf(GL_BACK,  GL_SHININESS, glconf.Shininess);

    for (n = 0; n < glconf.NLights; n++) {
        glLightModelf(GL_LIGHT_MODEL_TWO_SIDE, 1.0);
        glLightfv(GL_LIGHT0+n, GL_POSITION, glconf.LightPos[n]); 
        glLightfv(GL_LIGHT0+n, GL_DIFFUSE, glconf.LightDiffuseColor[n]); 
        glLightfv(GL_LIGHT0+n, GL_AMBIENT, glconf.LightAmbientColor[n]); 
        glLightfv(GL_LIGHT0+n, GL_SPECULAR, glconf.LightSpecularColor[n]); 
        glEnable(GL_LIGHT0+n);
    }
    glEnable(GL_LIGHTING);
}

void DrawWidget::setFrustum(double xoff, double yoff)
{
    double fx1, fx2, fy1, fy2;
    double th = glconf.VAngle/180.0*3.14159265358979;
    double faspect = (double)glconf.VWidth/(double)glconf.VHeight;
    double scale, dx, dy;

    fy1 = -glconf.ZNear*tan(th/2.0);
    fy2 = -fy1;
    fx1 = fy1*faspect;
    fx2 = fy2*faspect;

    scale = (fy2-fy1)/(double)glconf.VHeight;
    dx = scale*xoff;
    dy = scale*yoff;

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(fx1-dx, fx2-dx, fy1-dy, fy2-dy, glconf.ZNear, glconf.ZFar);
    glMatrixMode(GL_MODELVIEW);
}

void DrawWidget::toGLfloatColor(unsigned int color, GLfloat *acolor)
{
    unsigned int  color1 = color;
    unsigned int rgb_r, rgb_g, rgb_b;

    rgb_r = color1/0x01000000;
    if (rgb_r > 255) rgb_r = 255;
    color1 -= rgb_r*0x01000000;
    rgb_g = color1/0x00010000;
    if (rgb_g > 255) rgb_g = 255;
    color1 -= rgb_g*0x00010000;
    rgb_b = color1/0x00000100;
    if (rgb_b > 255) rgb_b = 255;
    color1 -= rgb_b*0x00000100;
    acolor[0] = (GLfloat)rgb_r/255.0f;
    acolor[1] = (GLfloat)rgb_g/255.0f;
    acolor[2] = (GLfloat)rgb_b/255.0f;
    acolor[3] = (GLfloat)color1/255.0f;
}

void DrawWidget::drawBalls()
{
    GLfloat aColor[4], sColor[4], eColor[4];
    unsigned long prevcolor = 0, color;
    int nquality2;
    int elem;
    double x, y, z, r;
    int n;
    GLUquadric* quad;
    int polyox = (glconf.NQuality < 10);

    if (moldata == 0) return;

    nquality2 = (glconf.NQuality*2)/3;

    sColor[0] = sColor[1] = sColor[2] = sColor[3] = 1.0f;
    eColor[0] = eColor[1] = eColor[2] = 0.0f; eColor[3] = 1.0f;

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); 
    int nions = moldata->NIons;
    if (nions >= 1) {
        quad = gluNewQuadric();
        gluQuadricNormals(quad, GLU_SMOOTH);
        gluQuadricTexture(quad, GL_TRUE);

        glMaterialfv(GL_FRONT, GL_SPECULAR, sColor);
        glMaterialfv(GL_FRONT, GL_EMISSION, eColor);
        for (n = 0; n < nions; n++) {
            moldata->getRotatedPos(n, &x, &y, &z);

            elem = moldata->Num[n];
            r = molconf.getBallRadius(elem)*molconf.BallRadiusFactor;
            color = molconf.getBallColor(elem);
            if (color != prevcolor) {
                prevcolor = color;
                toGLfloatColor(color, aColor);
                glMaterialfv(GL_FRONT, GL_AMBIENT,  aColor);
                glMaterialfv(GL_FRONT, GL_DIFFUSE,  aColor);
            }

            glPushMatrix ();
            glTranslatef((GLfloat)x, (GLfloat)y, (GLfloat)z);
            if (polyox) drawFilledCircle(r);
            else gluSphere(quad, (GLfloat)r, glconf.NQuality, nquality2);
            glPopMatrix ();
        }
        gluDeleteQuadric(quad);
        glDisable(GL_BLEND);
    }
}

#ifndef __NOSTICK__
void DrawWidget::drawSticks()
{
    GLfloat aColor[4], sColor[4] ,eColor[4];
    int ion1, ion2, elem1, elem2;
    unsigned long color;
    int nq = glconf.NQuality;
    double r, x1, y1, z1, x2, y2, z2;
    double q, dx1, dy1, dz1, dx2, dy2, dz2, dx3, dy3, dz3, q3, theta;
    int n;
    GLUquadric* quad;
    int polyox = (glconf.NQuality < 10);

    if (moldata == 0) return;

    sColor[0] = sColor[1] = sColor[2] = sColor[3] = 1.0f;
    eColor[0] = eColor[1] = eColor[2] = 0.0f;
    eColor[3] = 1.0f;

    if (!glconf.DrawStickOX) return;
    if (polyox) return;

    int nsticks = moldata->NSticks;
    if (nsticks < 0) {
        moldata->makeSticks();
        nsticks = moldata->NSticks;
    }

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); 
    dx1 = 0.0; dy1 = 0.0; dz1 = 1.0;
    quad = gluNewQuadric();
    gluQuadricNormals(quad, GLU_SMOOTH);
    gluQuadricTexture(quad, GL_TRUE);
    glMaterialfv(GL_FRONT, GL_SPECULAR, sColor);
    glMaterialfv(GL_FRONT, GL_EMISSION, eColor);
    for (n = 0; n < nsticks; n++) {
        ion1 = moldata->Ion1[n];
        ion2 = moldata->Ion2[n];
        elem1 = moldata->Num[ion1];
        elem2 = moldata->Num[ion2];
        r = molconf.getStickRadius(elem1, elem2);
        moldata->getRotatedPos(ion1, &x1, &y1, &z1);
        moldata->getRotatedPos(ion2, &x2, &y2, &z2);
        dx2 = x2-x1;
        dy2 = y2-y1;
        dz2 = z2-z1;
        q = sqrt(dx2*dx2+dy2*dy2+dz2*dz2);
        if (q > 0.0) {
            dx2 /= q;
            dy2 /= q;
            dz2 /= q;
            dx3 = dy1*dz2-dz1*dy2;
            dy3 = dz1*dx2-dx1*dz2;
            dz3 = dx1*dy2-dy1*dx2;
            q3 = sqrt(dx3*dx3+dy3*dy3+dz3*dz3);
            if (q3 > 0.0) {
                dx3 /= q3;
                dy3 /= q3;
                dz3 /= q3;
                theta = acos(dx1*dx2+dy1*dy2+dz1*dz2);
                theta *= 180.0/3.1415926535897932384626433832795;
            } else {
                dx3 = 1.0;
                dy3 = 0.0;
                dz3 = 0.0;
                if ((dx1*dx2+dy1*dy2+dz1*dz2) >= 0.0) {
                    theta = 0.0;
                } else {
                    theta = 180.0;
                }
            }

            glPushMatrix ();
            glTranslated(x1, y1, z1);
            glRotated(theta, dx3, dy3, dz3);

            color = molconf.getBallColor(elem1);
            toGLfloatColor(color, aColor);
            glMaterialfv(GL_FRONT, GL_DIFFUSE,  aColor);
            glMaterialfv(GL_FRONT, GL_AMBIENT,  aColor);
            gluCylinder(quad, r,  r, 0.5f*q, nq, 1);

            glTranslatef(0.0, 0.0, 0.5*q);
            color = molconf.getBallColor(elem2);
            toGLfloatColor(color, aColor);
            glMaterialfv(GL_FRONT, GL_DIFFUSE,  aColor);
            glMaterialfv(GL_FRONT, GL_AMBIENT,  aColor);
            gluCylinder(quad, r,  r, 0.5f*q, nq, 1);
            glPopMatrix ();
        }
    }
    gluDeleteQuadric(quad);
    glDisable(GL_BLEND);
}
#endif

void DrawWidget::drawIsosurfaces()
{
    GLfloat aColor[4], sColor[4];
    unsigned int color;
    int i, j, k, l;
    double rm[3][3];
    double r0[3];
    double r[3];

    if (moldata == 0) return;

    for (k = 0; k < 3; k++)
    for (l = 0; l < 3; l++) rm[k][l] = moldata->GC->RM[k][l];

    sColor[0] = sColor[1] = sColor[2] = sColor[3] = 1.0f;

    if (!moldata->Data3DOX) return;

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); 

    for (i = 0; i < 2; i++) {
        color = molconf.IsosurfaceColor[i];
        toGLfloatColor(color, aColor);

        glMaterialfv(GL_FRONT, GL_SPECULAR, aColor);
        glMaterialfv(GL_FRONT, GL_AMBIENT,  aColor);
        glMaterialfv(GL_FRONT, GL_DIFFUSE,  aColor);
        glMaterialfv(GL_BACK, GL_SPECULAR, aColor);
        glMaterialfv(GL_BACK, GL_AMBIENT,  aColor);
        glMaterialfv(GL_BACK, GL_DIFFUSE,  aColor);

        glBegin(GL_TRIANGLES);
        for (j = 0; j < moldata->NTriangle[i]; j++) {
            for (k = 0; k < 3; k++) {
                r0[0] = moldata->NormalVector0[i][9*j+3*k+0];
                r0[1] = moldata->NormalVector0[i][9*j+3*k+1];
                r0[2] = moldata->NormalVector0[i][9*j+3*k+2];
                r[0] = rm[0][0]*r0[0]+rm[0][1]*r0[1]+rm[0][2]*r0[2];
                r[1] = rm[1][0]*r0[0]+rm[1][1]*r0[1]+rm[1][2]*r0[2];
                r[2] = rm[2][0]*r0[0]+rm[2][1]*r0[1]+rm[2][2]*r0[2];
                glNormal3dv(r);
                r0[0] = moldata->Triangle0[i][9*j+3*k+0];
                r0[1] = moldata->Triangle0[i][9*j+3*k+1];
                r0[2] = moldata->Triangle0[i][9*j+3*k+2];
                r[0] = rm[0][0]*r0[0]+rm[0][1]*r0[1]+rm[0][2]*r0[2];
                r[1] = rm[1][0]*r0[0]+rm[1][1]*r0[1]+rm[1][2]*r0[2];
                r[2] = rm[2][0]*r0[0]+rm[2][1]*r0[1]+rm[2][2]*r0[2];
                glVertex3dv(r);
            }
        }
        glEnd();
    }

    glDisable(GL_BLEND);
}

void DrawWidget::drawFilledCircle(double r)
{
    int n;
    double v[3];
    static double nv[3] = {0.5, 0.5, 0.5};
    static double nv0[3] = {0.35, 0.35, 0.869};
    static double nv00[3] = {0.1, 0.1, 0.99};
    ///*
    static double x[9] = { 1.0, 0.707106781, 0.0, -0.707106781, -1.0,         
                          -0.707106781, 0.0, 0.707106781, 1.0};
    static double y[9] = { 0.0, 0.707106781, 1.0, 0.707106781, 0.0,         
                          -0.707106781, -1.0, -0.707106781,  0.0};
    if (moldata == 0) return ;

    glBegin(GL_POLYGON);
    glNormal3dv(nv);
    for (n = 0; n <= 8; n++) {
        v[0] = r*x[n];
        v[1] = r*y[n];
        v[2] = 0.0;
        glVertex3dv(v);
    }
    glEnd();
    glBegin(GL_POLYGON);
    glNormal3dv(nv0);
    for (n = 0; n <= 8; n++) {
        v[0] = 0.5*r*x[n];
        v[1] = 0.5*r*y[n];
        v[2] = 0.01;
        glVertex3dv(v);
    }
    glEnd();
    glBegin(GL_POLYGON);
    glNormal3dv(nv00);
    for (n = 0; n <= 8; n++) {
        v[0] = 0.2*r*x[n];
        v[1] = 0.2*r*y[n];
        v[2] = 0.02;
        glVertex3dv(v);
    }
    glEnd();
    //*/
}

void DrawWidget::OpenFile()
{
    QString fn = 0;
    char fn1[512];

    fn  = QFileDialog::getOpenFileName(this, tr("Select MolData file"),
                       QString::null, tr("All files (*)")); 

    if (fn == QString::null) return;

    strcpy(fn1, fn.toLocal8Bit().constData());
    openMolDataFile(fn1);
    updateGL();
}

void DrawWidget::RotateLeft(double deg)
{
    if (moldata == 0) return;
    moldata->rotateY(deg);
    updateGL();
}

void DrawWidget::RotateRight(double deg)
{
    if (moldata == 0) return;
    moldata->rotateY(-deg);
    updateGL();
}

void DrawWidget::RotateUp(double deg)
{
    if (moldata == 0) return;
    moldata->rotateX(deg);
    updateGL();
}

void DrawWidget::RotateDown(double deg)
{
    if (moldata == 0) return;
    moldata->rotateX(-deg);
    updateGL();
}

void DrawWidget::RotateClockWise(double deg)
{
    if (moldata == 0) return;
    moldata->rotateZ(deg);
    updateGL();
}

void DrawWidget::RotateCounterClockWise(double deg)
{
    if (moldata == 0) return;
    moldata->rotateZ(-deg);
    updateGL();
}

void DrawWidget::Unrotate()
{
    if (moldata == 0) return;
    moldata->unrotate();
    updateGL();
}

void DrawWidget::ToggleQuality()
{
    if (moldata == 0) return;
    if (glconf.NQuality == 8) {
        glconf.NQuality = 24;
    } else if (glconf.NQuality == 24) {
        glconf.NQuality = 60;
    } else {
        glconf.NQuality = 8;
    }

    updateGL();
}

void DrawWidget::ChangeQuality(int n)
{
    glconf.NQuality = n;
    updateGL();
}

void DrawWidget::SelectQuality(int defaultox)
{
    if (defaultox) {
        glconf.NQuality = 8;
    } else {
        QStringList items;
        items << tr("8") << tr("12") << tr("18") << tr("24");
        int current;
        current = (glconf.NQuality ==  8) ? 0 :
                  (glconf.NQuality == 12) ? 1 :
                  (glconf.NQuality == 18) ? 2 : 3;

        bool ok;
        QString item = QInputDialog::getItem(this,
                               tr("Change Quality"),
                               tr("Quality:"), items, current, false, &ok);
        if (ok && !item.isEmpty()) {
            glconf.NQuality = atoi(item.toLocal8Bit().data());
        }
    }

    updateGL();
}

void DrawWidget::ToggleAntiAlias()
{
    if (moldata == 0) return;
    glconf.AntiAliasOX = !glconf.AntiAliasOX;
    updateGL();
}

void DrawWidget::ToggleDrawStick()
{
    if (moldata == 0) return;
    glconf.DrawStickOX = !glconf.DrawStickOX;
    updateGL();
}

void DrawWidget::IncreaseBallSize(double sfactor)
{
    if (moldata == 0) return;
    if (molconf.BallRadiusFactor < 2.0) molconf.BallRadiusFactor *= sfactor;
    updateGL();
}

void DrawWidget::DecreaseBallSize(double sfactor)
{
    if (moldata == 0) return;
    if (molconf.BallRadiusFactor > 0.3) molconf.BallRadiusFactor /= sfactor;
    updateGL();
}

void DrawWidget::ZoomIn(double factor)
{
    if (moldata == 0) return;
    glconf.zoomIn(factor);
    updateGL();
}

void DrawWidget::ZoomOut(double factor)
{
    if (moldata == 0) return;
    glconf.zoomOut(factor);
    updateGL();
}

void DrawWidget::EyeUp(double factor)
{
    if (moldata == 0) return;
   
    glconf.EyePos[1] += (float)factor; ;
    glconf.LookAtPos[1] += (float)factor;
    updateGL();
}

void DrawWidget::EyeDown(double factor)
{
    if (moldata == 0) return;
   
    glconf.EyePos[1] -= (float)factor; 
    glconf.LookAtPos[1] -= (float)factor;
    updateGL();
}

void DrawWidget::EyeLeft(double factor)
{
    if (moldata == 0) return;
   
    glconf.EyePos[0] -= (float)factor; 
    glconf.LookAtPos[0] -= (float)factor;
    updateGL();
}

void DrawWidget::EyeRight(double factor)
{
    if (moldata == 0) return;
   
    glconf.EyePos[0] += (float)factor;
    glconf.LookAtPos[0] += (float)factor;
    updateGL();
}

void DrawWidget::MoveSceneUp(int v)
{
    if (moldata == 0) return;
    glconf.moveViewportUp(v);
    updateGL();
}

void DrawWidget::MoveSceneDown(int v)
{
    if (moldata == 0) return;
    glconf.moveViewportDown(v);
    updateGL();
}

void DrawWidget::MoveSceneLeft(int v)
{
    if (moldata == 0) return;
    glconf.moveViewportLeft(v);
    updateGL();
}

void DrawWidget::MoveSceneRight(int v)
{
    if (moldata == 0) return;
    glconf.moveViewportRight(v);
    updateGL();
}

void DrawWidget::ChangeIsosurfaceCutoff()
{
    if (moldata == 0) return;
    if (!moldata->Data3DOX) return;
    
    bool ok;
    double val = QInputDialog::getDouble(this, 
            tr("Isosurface Cutoff"), 
            tr("Enter your a cutoff value \n(0 < value < 1)"),
            molconf.IsosurfaceCutoff, 0.01, 0.99, 2, 
            &ok );
    if (!ok) return;

    int mode = QInputDialog::getInteger(this, 
            tr("Isosurface Cutoff"),
            tr("Enter a summation mode \n(0: sum of abs, 1:sum of squares)"),
            molconf.IsosurfaceSumMode, 0, 1, 1,
            &ok );
    if (!ok) return;

    molconf.IsosurfaceCutoff = val;
    molconf.IsosurfaceSumMode = mode;
    int nit;
    double ival;
    moldata->makeIsosurfaces(&nit, &ival);
    char str[512];
    sprintf(str, "[iterations: %d] isosurface at %f (%.1f %% inside)", 
            nit, ival, molconf.IsosurfaceCutoff*100.0);
    QMessageBox::about(this, "isosurface cutoof", str);
    updateGL();
}

void DrawWidget::ChangeGLConf(int defaultox)
{
    if (defaultox) {
        glconf.setDefaultGLConf();
    } else {
        QString fn = 0;
        char fn1[512];

        fn  = QFileDialog::getOpenFileName(this, tr("Select GLConf file"),
                           QString::null, tr("GLConf files (*.glconf)")); 

        if (fn == QString::null) return;

        strcpy(fn1, fn.toLocal8Bit().constData());
        glconf.loadGLConfFile(fn1); 


    }
    updateGL();
}

void DrawWidget::ChangeMolConf(int defaultox)
{
    if (defaultox) {
        // if (molconf.isMolConfFileLoaded()) {
            molconf.setDefaultMolConf();
            moldata->identify();
#ifndef __NOSTICK__
            moldata->makeSticks();
#endif
        // }
    } else {
        QString fn = 0;
        char fn1[512];

        fn  = QFileDialog::getOpenFileName(this, tr("Select MolConf file"),
                           QString::null, tr("molconf files (*.molconf)")); 

        if (fn == QString::null) return;

        strcpy(fn1, fn.toLocal8Bit().constData());
        molconf.loadMolConfFile(fn1);
        moldata->identify();
#ifndef __NOSTICK__
        moldata->makeSticks();
#endif
    }
    updateGL();
}

class Sleeper : public QThread
{
public:
    static void usleep(unsigned long usecs){QThread::usleep(usecs);}
    static void msleep(unsigned long msecs){QThread::msleep(msecs);}
    static void sleep(unsigned long secs){QThread::sleep(secs);}
};

QPixmap DrawWidget::makePixmap()
{
    int w = width();
    int h = height();
    int vwidth, vheight, vx0, vy0, vx1, vy1;
    int nx, ny, mx, my;
    char str[512];
    vwidth = glconf.VWidth; 
    vheight = glconf.VHeight; 
    vx0 = glconf.VX0;
    vy0 = glconf.VY0;
    QPixmap pixmap = QPixmap(vwidth, vheight);
    QPainter painter(&pixmap);
    QPixmap pmp;

    int r, g, b;
    r = (int)floor(glconf.BGColor[0]*255.0+0.5);
    g = (int)floor(glconf.BGColor[1]*255.0+0.5);
    b = (int)floor(glconf.BGColor[2]*255.0+0.5);
    pixmap.fill(QColor(r,g,b));

    nx = (int)ceil((double)vwidth/(double)w);
    ny = (int)ceil((double)vheight/(double)h);
    vx1 = (vwidth-w)/2;
    vy1 = (vheight-h)/2;
    for (mx = 0; mx < nx; mx++) {
        for (my = 0; my < ny; my++) {
            glconf.VX0 = vx1-w*mx;
            glconf.VY0 = vy1-vheight+h*(my+1);
            updateGL(); 
            paintGL();
            Sleeper::msleep(100);
            pmp = QPixmap::grabWindow(winId());
            painter.drawPixmap(w*mx, h*my, pmp);
            //Sleeper::msleep(300);
            sprintf(str, "(%d, %d) of (%d, %d)\nPress OK button.", 
                   mx+1, my+1, nx, ny);
            QMessageBox::about(this, "Making an image in full scale", str);
        }
    }
    glconf.VX0 = vx0;
    glconf.VY0 = vy0;
    updateGL();
    return pixmap;
}

void DrawWidget::CopyImageToClipboard()
{
    //QPixmap pmp = QPixmap::grabWindow(winId());
    QPixmap pmp = makePixmap();
    qApp->clipboard()->setPixmap(pmp);
}

void DrawWidget::SaveImageFile()
{
    //QPixmap pmp = QPixmap::grabWindow(winId());
    QPixmap pmp = makePixmap();

    QString fn = 0;
    char fn1[512];

    fn  = QFileDialog::getSaveFileName(this, tr("File name to save image"),
                       QString::null, tr("PNG files (*.png)")); 

    if (fn == QString::null) return;

    strcpy(fn1, fn.toLocal8Bit().constData());

   pmp.save(fn1, "PNG");
}

void DrawWidget::SaveGLConfFile()
{
    QPixmap pmp = QPixmap::grabWindow(winId());

    QString fn = 0;
    char fn1[512];

    fn  = QFileDialog::getSaveFileName(this, 
                       tr("File name to save GLConf file"),
                       QString::null, tr("GLConf files (*.glconf)")); 

    if (fn == QString::null) return;

    strcpy(fn1, fn.toLocal8Bit().constData());

    glconf.SaveGLConfFile(fn1);
}

void DrawWidget::replaceMolecules()
{
    MolData *moldata1 = 0;
    QString fn1 = 0;
    char fn[512];

    fn1  = QFileDialog::getOpenFileName(this, tr("Select MolData file"),
                       QString::null, tr("All files (*)")); 

    if (fn1 == QString::null) return;

    strcpy(fn, fn1.toLocal8Bit().constData());

    char ext[256], basename[256];
    MolData::GetFileNameExtension(fn, ext);
    MolData::GetFileBaseName(fn, basename);

    if (strcmp(basename, "I_info") == 0) {
        moldata1 = new I_info(fn, &glconf, &molconf);
    } else if (strcmp(basename, "POSCAR") == 0) {
        moldata1 = new POSCARFile(fn, &glconf, &molconf);
    } else if (strcmp(basename, "CONTCAR") == 0) {
        moldata1 = new POSCARFile(fn, &glconf, &molconf);
    } else if (strcmp(ext, "cube") == 0) {
        int nit;
        double val;
        moldata1 = new CubeFile(fn, &glconf, &molconf);
        moldata1->makeIsosurfaces(&nit, &val);
    } else if (strcmp(ext, "xyz") == 0) {
        moldata1 = new XYZFile(fn, &glconf, &molconf);
    } else if (strcmp(ext, "POSCAR") == 0) {
        moldata1 = new POSCARFile(fn, &glconf, &molconf);
    } else if (strcmp(ext, "I_info") == 0) {
        moldata1 = new I_info(fn, &glconf, &molconf);
    }
    if (moldata1 != 0) {
        if (moldata1->NIons > 0) {
            moldata->replaceMolecules(moldata1);
            delete moldata1;
            updateGL();
        }
    }

}

