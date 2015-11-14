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
#ifndef __MAINWINDOW_H
#define __MAINWINDOW_H

#include <QMainWindow>
#include <QAction>
#include <QMenuBar>

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow(QWidget *parent = 0); //, const char *name = 0);


    void createActions();
    void createMenus();
    void createToolBars();
    
    //int ControlPressed;
    //int ShiftPressed;

    void keyPressEvent( QKeyEvent *e );
    void keyReleaseEvent( QKeyEvent *e );

private slots:
    void about();

    void openFile();
    void saveImage();
    void copyImage();

    void unrotate();

    void rotateXAxisP();
    void rotateYAxisP();
    void rotateZAxisP();
    void rotateXAxisM();
    void rotateYAxisM();
    void rotateZAxisM();

    void zoomIn();
    void zoomOut();

    void toggleAntiAlias();
    void toggleQuality();
    void changeQuality();

    void changeGLConf();
    void changeMolConf();

    void toggleStickDraw();
    void increaseBallSize();
    void decreaseBallSize();
    
    void moveSceneUp();
    void moveSceneDown();
    void moveSceneLeft();
    void moveSceneRight();

    void saveGLConfFile();

    void replaceMolecules();

private:

};

#endif

