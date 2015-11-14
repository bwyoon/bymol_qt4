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
#include <QMessageBox>
#include <QAction>
#include <QToolBar>
#include "MainWindow.h"
#include "DrawWidget.h"

int ControlPressed, ShiftPressed;

MainWindow::MainWindow(QWidget *parent) //, const char *name) 
: QMainWindow(parent) //, name)
{
    int argc = qApp->argc();
    char ** argv = qApp->argv();

    setWindowIcon(QIcon(QPixmap(":/icon.png")));
  
    DrawWidget *w = new DrawWidget((argc < 2) ? 0 : argv[1], this);
    setCentralWidget(w);

    createMenus();
    createToolBars();

    ControlPressed = 0;
    ShiftPressed = 0;
}

void MainWindow::createActions()
{
}

void MainWindow::createMenus()
{
    //DrawWidget *w = (DrawWidget *)centralWidget();

    QMenu *filemenu = menuBar()->addMenu("&File");

        QPixmap openpix(":/fileopen.png");
        QPixmap savepix(":/filesave.png");

        QAction *openmenu = new QAction(openpix, "&Open", this);
        QAction *savemenu = new QAction(savepix, "&Save", this);
        QAction *quitmenu = new QAction("&Quit", this);

        connect(openmenu, SIGNAL(triggered()), this, SLOT(openFile()));
        connect(savemenu, SIGNAL(triggered()), this, SLOT(saveImage()));
        connect(quitmenu, SIGNAL(triggered()), this, SLOT(close()));

        filemenu->addAction(openmenu);
        filemenu->addAction(savemenu);
        filemenu->addSeparator();
        filemenu->addAction(quitmenu);
    
    QMenu *editmenu = menuBar()->addMenu("&Edit");

        QAction *copymenu = new QAction("&Copy", this);
        copymenu->setShortcut(tr("CTRL+C"));
        connect(copymenu, SIGNAL(triggered()), this, SLOT(copyImage()));

        editmenu->addAction(copymenu);

    QMenu *moldatamenu = menuBar()->addMenu("MolData");

        QAction *rposmenu = new QAction("Replace Molecules", this);
        connect(rposmenu, SIGNAL(triggered()), this, SLOT(replaceMolecules()));

        moldatamenu->addAction(rposmenu);
       

    QMenu *rendermenu = menuBar()->addMenu("&Rendering");

        QAction *moveupmenu = new QAction("Move Scene Up", this);
        QAction *movedownmenu = new QAction("Move Scene Down", this);
        QAction *moveleftmenu = new QAction("Move Scene Left", this);
        QAction *moverightmenu = new QAction("Move Scene Right", this);
        QAction *unrotatemenu = new QAction("Unrotate", this);
        QAction *saveglconfmenu = new QAction("Save GLConf file", this);
        connect(moveupmenu, SIGNAL(triggered()), this, SLOT(moveSceneUp()));
        connect(movedownmenu, SIGNAL(triggered()), this, SLOT(moveSceneDown()));
        connect(moveleftmenu, SIGNAL(triggered()), this, SLOT(moveSceneLeft()));
        connect(unrotatemenu, SIGNAL(triggered()), this, SLOT(unrotate()));
        connect(saveglconfmenu, SIGNAL(triggered()), this, SLOT(saveGLConfFile()));

        rendermenu->addAction(moveupmenu);
        rendermenu->addAction(movedownmenu);
        rendermenu->addSeparator();
        rendermenu->addAction(moveleftmenu);
        rendermenu->addAction(moverightmenu);
        rendermenu->addSeparator();
        rendermenu->addAction(unrotatemenu);
        rendermenu->addSeparator();
        rendermenu->addAction(saveglconfmenu);

    QMenu *helpmenu = menuBar()->addMenu("&Help");

        QAction *aboutmenu = new QAction("&About", this);
        connect(aboutmenu, SIGNAL(triggered()), this, SLOT(about()));

        helpmenu->addAction(aboutmenu);

    /*
    QPopupMenu *isoMenu = new QPopupMenu(this);
    menuBar()->insertItem(tr("&Rendering"), isoMenu);
    isoMenu->insertItem("Change cutoff level", this, SLOT(changeCutoffLevel()));
    */
}

void MainWindow::createToolBars()
{
    QToolBar *toolbar = addToolBar("main tool bar");

    QPixmap openpix(":/fileopen.png");
    QAction *openmenu = toolbar->addAction(QIcon(openpix), "Open File");
    connect(openmenu, SIGNAL(triggered()), this, SLOT(openFile()));

    QPixmap savepix(":/filesave.png");
    QAction *savemenu = toolbar->addAction(QIcon(savepix), "Save Image");
    connect(savemenu, SIGNAL(triggered()), this, SLOT(saveImage()));

    toolbar->addSeparator();

    QPixmap copypix(":/editcopy.png");
    QAction *copymenu = toolbar->addAction(QIcon(copypix), "Copy Image");
    connect(copymenu, SIGNAL(triggered()), this, SLOT(copyImage()));

    toolbar->addSeparator();

    QPixmap rotxmpix(":/rotxm.png");
    QAction *rotxmmenu = toolbar->addAction(QIcon(rotxmpix), "X-axis rotaion (-)");
    connect(rotxmmenu, SIGNAL(triggered()), this, SLOT(rotateXAxisM()));

    QPixmap rotxppix(":/rotxp.png");
    QAction *rotxpmenu = toolbar->addAction(QIcon(rotxppix), "X-axis rotaion (+)");
    connect(rotxpmenu, SIGNAL(triggered()), this, SLOT(rotateXAxisP()));

    QPixmap rotympix(":/rotym.png");
    QAction *rotymmenu = toolbar->addAction(QIcon(rotympix), "Y-axis rotaion (-)");
    connect(rotymmenu, SIGNAL(triggered()), this, SLOT(rotateYAxisM()));

    QPixmap rotyppix(":/rotyp.png");
    QAction *rotypmenu = toolbar->addAction(QIcon(rotyppix), "Y-axis rotaion (+)");
    connect(rotypmenu, SIGNAL(triggered()), this, SLOT(rotateYAxisP()));

    QPixmap rotzmpix(":/rotzm.png");
    QAction *rotzmmenu = toolbar->addAction(QIcon(rotzmpix), "Z-axis rotaion (-)");
    connect(rotzmmenu, SIGNAL(triggered()), this, SLOT(rotateZAxisM()));

    QPixmap rotzppix(":/rotzp.png");
    QAction *rotzpmenu = toolbar->addAction(QIcon(rotzppix), "Z-axis rotaion (+)");
    connect(rotzpmenu, SIGNAL(triggered()), this, SLOT(rotateZAxisP()));

    toolbar->addSeparator();

    QPixmap stickpix(":/stick.png");
    QAction *stickmenu = toolbar->addAction(QIcon(stickpix), "Toggle Stick Drawing");
    connect(stickmenu, SIGNAL(triggered()), this, SLOT(toggleStickDraw()));

    QPixmap bigballpix(":/bigball.png");
    QAction *bigballmenu = toolbar->addAction(QIcon(bigballpix), "Increase Ball Size");
    connect(bigballmenu, SIGNAL(triggered()), this, SLOT(increaseBallSize()));

    QPixmap smallballpix(":/smallball.png");
    QAction *smallballmenu = toolbar->addAction(QIcon(smallballpix), "Decrease Ball Size");
    connect(smallballmenu, SIGNAL(triggered()), this, SLOT(decreaseBallSize()));

    toolbar->addSeparator();

    QPixmap zoominpix(":/zoomin.png");
    QAction *zoominmenu = toolbar->addAction(QIcon(zoominpix), "Zoom In");
    connect(zoominmenu, SIGNAL(triggered()), this, SLOT(zoomIn()));

    QPixmap zoomoutpix(":/zoomout.png");
    QAction *zoomoutmenu = toolbar->addAction(QIcon(zoomoutpix), "Zoom Out");
    connect(zoomoutmenu, SIGNAL(triggered()), this, SLOT(zoomOut()));

    toolbar->addSeparator();

    QPixmap qualitypix(":/quality.png");
    QAction *qualitymenu = toolbar->addAction(QIcon(qualitypix), "Change Quality");
    connect(qualitymenu, SIGNAL(triggered()), this, SLOT(changeQuality()));

    QPixmap antialiaspix(":/antialias.png");
    QAction *antialiasmenu = toolbar->addAction(QIcon(antialiaspix), "Toggle Anti-Aliasing");
    connect(antialiasmenu, SIGNAL(triggered()), this, SLOT(toggleAntiAlias()));

    toolbar->addSeparator();

    QPixmap glconfpix(":/glconf.png");
    QAction *glconfmenu = toolbar->addAction(QIcon(glconfpix), "Open GLconf file or reset to default (with Ctrl Key pressed)");
    connect(glconfmenu, SIGNAL(triggered()), this, SLOT(changeGLConf()));

    QPixmap molconfpix(":/molconf.png");
    QAction *molconfmenu = toolbar->addAction(QIcon(molconfpix), "Open iMolConf file or reset to default (with Ctrl Key pressed)");
    connect(molconfmenu, SIGNAL(triggered()), this, SLOT(changeMolConf()));
}

void MainWindow::keyPressEvent( QKeyEvent *e )
{
    DrawWidget *w = (DrawWidget*)centralWidget();
    switch( e->key() ) {
        case Qt::Key_Control:
            ControlPressed = 1;
            break;

        case Qt::Key_Shift:
            ShiftPressed = 1;
            break;

        case Qt::Key_Left:
            w->RotateLeft(ShiftPressed? 90.0 : (ControlPressed ? 1.0 : 10.0));
            break;
        case Qt::Key_Right:
            w->RotateRight(ShiftPressed? 90.0 : (ControlPressed ? 1.0 : 10.0));
            break;
        case Qt::Key_Up:
            w->RotateUp(ShiftPressed? 90.0 : (ControlPressed ? 1.0 : 10.0));
            break;
        case Qt::Key_Down:
            w->RotateDown(ShiftPressed? 90.0 : (ControlPressed ? 1.0 : 10.0));
            break;
        case Qt::Key_Home:
            w->RotateCounterClockWise(ShiftPressed? 90.0 : (ControlPressed ? 1.0 : 10.0));
            break;
        case Qt::Key_End:
            w->RotateClockWise(ShiftPressed? 90.0 : (ControlPressed ? 1.0 : 10.0));
            break;
        case Qt::Key_Insert:
            w->Unrotate();
            break;

        case Qt::Key_Plus:
            //w->EyeDown(5.0);
            w->MoveSceneUp(200);
            break;
        case Qt::Key_Equal:
            //w->EyeDown(ControlPressed ? 0.05 : 0.5);
            w->MoveSceneUp(ControlPressed ? 2 : 20);
            break;
        case Qt::Key_Underscore:
            //w->EyeUp(5.0);
            w->MoveSceneDown(200);
            break;
        case Qt::Key_Minus:
            //w->EyeUp(ControlPressed ? 0.05 : 0.5);
            w->MoveSceneDown(ControlPressed ? 2 : 20);
            break;
        case Qt::Key_Less:
            //w->EyeRight(5.0);
            w->MoveSceneLeft(200);
            break;
        case Qt::Key_Greater:
            //w->EyeLeft(5.0);
            w->MoveSceneRight(200);
            break;
        case Qt::Key_Comma:
            //w->EyeRight(ControlPressed ? 0.05 : 0.5);
            w->MoveSceneLeft(ControlPressed ? 2 : 20);
            break;
        case Qt::Key_Period:
            //w->EyeLeft(ControlPressed ? 0.05 : 0.5);
            w->MoveSceneRight(ControlPressed ? 2 : 20);
            break;

        case Qt::Key_Q:
            //w->ToggleQuality();
#ifdef __FOR_BIG_SYSTEM
            w->ChangeQuality(ControlPressed ? 8 : ShiftPressed ? 18 : 12);
#else
            w->ChangeQuality(ControlPressed ? 15 : ShiftPressed ? 60 : 30);
#endif

            break;
        case Qt::Key_A:
            w->ToggleAntiAlias();
            break;
        case Qt::Key_S:
            w->ToggleDrawStick();
            break;

        case Qt::Key_I:
            w->ZoomIn(ShiftPressed? pow(1.05, 25.0) : ControlPressed ? 1.05 : pow(1.05, 5.0));
            break;
        case Qt::Key_O:
            w->ZoomOut(ShiftPressed? pow(1.05, 25.0) : ControlPressed ? 1.05 : pow(1.05, 5.0));
            break;

        case Qt::Key_0:
            w->IncreaseBallSize(ShiftPressed ? 1.5 : 1.1);
            break;
        case Qt::Key_9:
            w->DecreaseBallSize(ShiftPressed ? 1.5 : 1.1);
            break;

        case Qt::Key_F12:
            w->ChangeIsosurfaceCutoff();
            break;

  }
}

void MainWindow::keyReleaseEvent(QKeyEvent *e )
{
    switch( e->key() ) {
        case Qt::Key_Control:
            ControlPressed = 0;
            break;
        case Qt::Key_Shift:
            ShiftPressed = 0;
            break;
    }
}

void MainWindow::about()
{
    QMessageBox::about(this, "about bymol",
	    "<h3>bymol : molecular visualization software</h3>"
		"programmed by <b>Bokwon Yoon</b>, PhD. <br />"
		"School of Physics, Georgia Tech <br />"
		"This software is based on the software 3DView "
                "which is originally developed also by Bokwon Yoon "
                "in 1998, and upgraded by himself thereafter.<br /><br />"
		"(c) Copyright 2011 - , Bokwon Yoon<br /><br />");
}

void MainWindow::openFile()
{
    ((DrawWidget*)centralWidget())->OpenFile();
}


void MainWindow::saveImage()
{
    ((DrawWidget*)centralWidget())->SaveImageFile();
}

void MainWindow::copyImage()
{
    ((DrawWidget*)centralWidget())->CopyImageToClipboard();
}

void MainWindow::unrotate()
{
    ((DrawWidget*)centralWidget())->Unrotate();
}

void MainWindow::rotateXAxisP()
{
    ((DrawWidget*)centralWidget())->RotateDown(ShiftPressed? 90.0 : (ControlPressed ? 1.0 : 10.0));
}

void MainWindow::rotateXAxisM()
{
    ((DrawWidget*)centralWidget())->RotateUp(ShiftPressed? 90.0 : (ControlPressed ? 1.0 : 10.0));
}

void MainWindow::rotateYAxisP()
{
    ((DrawWidget*)centralWidget())->RotateRight(ShiftPressed? 90.0 : (ControlPressed ? 1.0 : 10.0));
}

void MainWindow::rotateYAxisM()
{
    ((DrawWidget*)centralWidget())->RotateLeft(ShiftPressed? 90.0 : (ControlPressed ? 1.0 : 10.0));
}

void MainWindow::rotateZAxisP()
{
    ((DrawWidget*)centralWidget())->RotateCounterClockWise(ShiftPressed? 90.0 : (ControlPressed ? 1.0 : 10.0));
}

void MainWindow::rotateZAxisM()
{
    ((DrawWidget*)centralWidget())->RotateClockWise(ShiftPressed? 90.0 : (ControlPressed ? 1.0 : 10.0));
}

void MainWindow::zoomIn()
{
    ((DrawWidget*)centralWidget())->ZoomIn(ShiftPressed? pow(1.05, 25.0) : ControlPressed ? 1.05 : pow(1.05, 5.0));
}

void MainWindow::zoomOut()
{
    ((DrawWidget*)centralWidget())->ZoomOut(ShiftPressed? pow(1.05, 25.0) : ControlPressed ? 1.05 : pow(1.05, 5.0));
}

void MainWindow::toggleStickDraw()
{
    ((DrawWidget*)centralWidget())->ToggleDrawStick();
}

void MainWindow::increaseBallSize()
{
    ((DrawWidget*)centralWidget())->IncreaseBallSize(ShiftPressed ? 1.5 : 1.1);
}

void MainWindow::decreaseBallSize()
{
    ((DrawWidget*)centralWidget())->DecreaseBallSize(ShiftPressed ? 1.5 : 1.1);
}

void MainWindow::toggleAntiAlias()
{
    ((DrawWidget*)centralWidget())->ToggleAntiAlias();
}

void MainWindow::toggleQuality()
{
    ((DrawWidget*)centralWidget())->ToggleQuality();
}

void MainWindow::changeQuality()
{
#ifdef __FOR_BIG_SYSTEM
    ((DrawWidget*)centralWidget())->ChangeQuality(ControlPressed ? 8: ShiftPressed ?  18: 12);
#else
    ((DrawWidget*)centralWidget())->ChangeQuality(ControlPressed ? 15: ShiftPressed ?  60: 30);
#endif
}

void MainWindow::changeGLConf()
{
    ((DrawWidget*)centralWidget())->ChangeGLConf(ControlPressed);
}

void MainWindow::changeMolConf()
{
    ((DrawWidget*)centralWidget())->ChangeMolConf(ControlPressed);
}

void MainWindow::moveSceneUp()
{
    ((DrawWidget*)centralWidget())->EyeDown(0.0005);
}

void MainWindow::moveSceneDown()
{
    ((DrawWidget*)centralWidget())->EyeUp(0.0005);
}

void MainWindow::moveSceneLeft()
{
    ((DrawWidget*)centralWidget())->EyeRight(0.0005);
}

void MainWindow::moveSceneRight()
{
    ((DrawWidget*)centralWidget())->EyeLeft(0.0005);
}

void MainWindow::saveGLConfFile()
{
    ((DrawWidget*)centralWidget())->SaveGLConfFile();
}

void MainWindow::replaceMolecules()
{
    ((DrawWidget*)centralWidget())->replaceMolecules();
}

