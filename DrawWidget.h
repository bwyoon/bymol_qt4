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

#ifndef __DRAWWIDGET_H
#define __DRAWWIDGET_H

#include <QApplication>
#include <QtOpenGL>
#include "MolData.h"
#include "GLConf.h"


class DrawWidget : public QGLWidget
{
public:
    DrawWidget(char *, QWidget *parent = 0); //, const char *name=0);

    GLConf glconf;
    MolData *moldata;
    MolConf molconf;

    void dragEnterEvent(QDragEnterEvent *);
    void dropEvent(QDropEvent *);

    void initializeGL();
    void resizeGL(int, int);
    void paintGL();

    void initScene();

    void setFrustum(double, double);

    void drawBalls();
#ifndef __NOSTICK__
    void drawSticks();
#endif
    void drawIsosurfaces();
    void drawFilledCircle(double);


    void openMolDataFile(char *);
    void OpenFile();

    void RotateLeft(double);
    void RotateRight(double);
    void RotateUp(double);
    void RotateDown(double);
    void RotateClockWise(double);
    void RotateCounterClockWise(double);
    void Unrotate();

    void ZoomIn(double factor);
    void ZoomOut(double factor);

    void EyeUp(double factor);
    void EyeDown(double factor);
    void EyeLeft(double factor);
    void EyeRight(double factor);

    void MoveSceneUp(int);
    void MoveSceneDown(int);
    void MoveSceneLeft(int);
    void MoveSceneRight(int);

    void ToggleQuality();
    void ChangeQuality(int);
    void SelectQuality(int);
    void ToggleAntiAlias();
    void ToggleDrawStick();

    void IncreaseBallSize(double);
    void DecreaseBallSize(double);

    void ChangeIsosurfaceCutoff();
    void ChangeGLConf(int);
    void ChangeMolConf(int);


    QPixmap makePixmap();
    void CopyImageToClipboard();
    void SaveImageFile();
    void SaveGLConfFile();

    void toGLfloatColor(unsigned int , GLfloat *);

    void replaceMolecules();
      
}; 

#endif
