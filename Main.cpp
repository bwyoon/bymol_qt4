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
#include <QGLFormat>
#include "MainWindow.h"

int main(int argc, char *argv[])
{
    QApplication::setColorSpec( QApplication::CustomColor );
    QApplication app(argc, argv);
    app.setWindowIcon(QIcon("icon.png"));

    ///*
    QGLFormat glf = QGLFormat::defaultFormat();
    glf.setSampleBuffers(true);
    glf.setSamples(4);
    QGLFormat::setDefaultFormat(glf);
    //*/

    MainWindow mainwin;
    mainwin.show();

    return app.exec();
}
