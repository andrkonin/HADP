/****************************************************************************
** Meta object code from reading C++ file 'pmd.h'
**
** Created: Tue Jun 16 10:50:00 2009
**      by: The Qt Meta Object Compiler version 61 (Qt 4.5.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "pmd.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'pmd.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 61
#error "This file was generated using the moc from 4.5.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_PMD[] = {

 // content:
       2,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   12, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors

 // slots: signature, parameters, type, tag, flags
       5,    4,    4,    4, 0x0a,
      18,    4,    4,    4, 0x0a,
      32,    4,    4,    4, 0x0a,
      45,    4,    4,    4, 0x0a,
      73,   61,    4,    4, 0x0a,
     100,    4,    4,    4, 0x0a,
     110,    4,    4,    4, 0x0a,
     123,    4,    4,    4, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_PMD[] = {
    "PMD\0\0changeView()\0backDefault()\0"
    "PMDConnect()\0PMDDisconnect()\0sbegin,send\0"
    "showLayer(QString,QString)\0pmdauto()\0"
    "pmdtopview()\0pmdquadspoints()\0"
};

const QMetaObject PMD::staticMetaObject = {
    { &QGLWidget::staticMetaObject, qt_meta_stringdata_PMD,
      qt_meta_data_PMD, 0 }
};

const QMetaObject *PMD::metaObject() const
{
    return &staticMetaObject;
}

void *PMD::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_PMD))
        return static_cast<void*>(const_cast< PMD*>(this));
    return QGLWidget::qt_metacast(_clname);
}

int PMD::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QGLWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: changeView(); break;
        case 1: backDefault(); break;
        case 2: PMDConnect(); break;
        case 3: PMDDisconnect(); break;
        case 4: showLayer((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 5: pmdauto(); break;
        case 6: pmdtopview(); break;
        case 7: pmdquadspoints(); break;
        default: ;
        }
        _id -= 8;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
