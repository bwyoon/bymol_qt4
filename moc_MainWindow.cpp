/****************************************************************************
** Meta object code from reading C++ file 'MainWindow.h'
**
** Created: Wed May 9 23:01:14 2012
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "MainWindow.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'MainWindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_MainWindow[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
      27,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      12,   11,   11,   11, 0x08,
      20,   11,   11,   11, 0x08,
      31,   11,   11,   11, 0x08,
      43,   11,   11,   11, 0x08,
      55,   11,   11,   11, 0x08,
      66,   11,   11,   11, 0x08,
      81,   11,   11,   11, 0x08,
      96,   11,   11,   11, 0x08,
     111,   11,   11,   11, 0x08,
     126,   11,   11,   11, 0x08,
     141,   11,   11,   11, 0x08,
     156,   11,   11,   11, 0x08,
     165,   11,   11,   11, 0x08,
     175,   11,   11,   11, 0x08,
     193,   11,   11,   11, 0x08,
     209,   11,   11,   11, 0x08,
     225,   11,   11,   11, 0x08,
     240,   11,   11,   11, 0x08,
     256,   11,   11,   11, 0x08,
     274,   11,   11,   11, 0x08,
     293,   11,   11,   11, 0x08,
     312,   11,   11,   11, 0x08,
     326,   11,   11,   11, 0x08,
     342,   11,   11,   11, 0x08,
     358,   11,   11,   11, 0x08,
     375,   11,   11,   11, 0x08,
     392,   11,   11,   11, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_MainWindow[] = {
    "MainWindow\0\0about()\0openFile()\0"
    "saveImage()\0copyImage()\0unrotate()\0"
    "rotateXAxisP()\0rotateYAxisP()\0"
    "rotateZAxisP()\0rotateXAxisM()\0"
    "rotateYAxisM()\0rotateZAxisM()\0zoomIn()\0"
    "zoomOut()\0toggleAntiAlias()\0toggleQuality()\0"
    "changeQuality()\0changeGLConf()\0"
    "changeMolConf()\0toggleStickDraw()\0"
    "increaseBallSize()\0decreaseBallSize()\0"
    "moveSceneUp()\0moveSceneDown()\0"
    "moveSceneLeft()\0moveSceneRight()\0"
    "saveGLConfFile()\0replaceMolecules()\0"
};

const QMetaObject MainWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_MainWindow,
      qt_meta_data_MainWindow, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &MainWindow::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow))
        return static_cast<void*>(const_cast< MainWindow*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: about(); break;
        case 1: openFile(); break;
        case 2: saveImage(); break;
        case 3: copyImage(); break;
        case 4: unrotate(); break;
        case 5: rotateXAxisP(); break;
        case 6: rotateYAxisP(); break;
        case 7: rotateZAxisP(); break;
        case 8: rotateXAxisM(); break;
        case 9: rotateYAxisM(); break;
        case 10: rotateZAxisM(); break;
        case 11: zoomIn(); break;
        case 12: zoomOut(); break;
        case 13: toggleAntiAlias(); break;
        case 14: toggleQuality(); break;
        case 15: changeQuality(); break;
        case 16: changeGLConf(); break;
        case 17: changeMolConf(); break;
        case 18: toggleStickDraw(); break;
        case 19: increaseBallSize(); break;
        case 20: decreaseBallSize(); break;
        case 21: moveSceneUp(); break;
        case 22: moveSceneDown(); break;
        case 23: moveSceneLeft(); break;
        case 24: moveSceneRight(); break;
        case 25: saveGLConfFile(); break;
        case 26: replaceMolecules(); break;
        default: ;
        }
        _id -= 27;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
