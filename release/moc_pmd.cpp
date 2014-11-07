/****************************************************************************
** Meta object code from reading C++ file 'pmd.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.3.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../pmd.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'pmd.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.3.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_PMD_t {
    QByteArrayData data[16];
    char stringdata[148];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_PMD_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_PMD_t qt_meta_stringdata_PMD = {
    {
QT_MOC_LITERAL(0, 0, 3),
QT_MOC_LITERAL(1, 4, 11),
QT_MOC_LITERAL(2, 16, 0),
QT_MOC_LITERAL(3, 17, 5),
QT_MOC_LITERAL(4, 23, 10),
QT_MOC_LITERAL(5, 34, 11),
QT_MOC_LITERAL(6, 46, 8),
QT_MOC_LITERAL(7, 55, 11),
QT_MOC_LITERAL(8, 67, 10),
QT_MOC_LITERAL(9, 78, 13),
QT_MOC_LITERAL(10, 92, 9),
QT_MOC_LITERAL(11, 102, 6),
QT_MOC_LITERAL(12, 109, 4),
QT_MOC_LITERAL(13, 114, 7),
QT_MOC_LITERAL(14, 122, 10),
QT_MOC_LITERAL(15, 133, 14)
    },
    "PMD\0changeValue\0\0value\0changeView\0"
    "showinvalid\0showgrid\0backDefault\0"
    "PMDConnect\0PMDDisconnect\0showLayer\0"
    "sbegin\0send\0pmdauto\0pmdtopview\0"
    "pmdquadspoints"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_PMD[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      11,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   69,    2, 0x0a /* Public */,
       4,    0,   72,    2, 0x0a /* Public */,
       5,    0,   73,    2, 0x0a /* Public */,
       6,    0,   74,    2, 0x0a /* Public */,
       7,    0,   75,    2, 0x0a /* Public */,
       8,    0,   76,    2, 0x0a /* Public */,
       9,    0,   77,    2, 0x0a /* Public */,
      10,    2,   78,    2, 0x0a /* Public */,
      13,    0,   83,    2, 0x0a /* Public */,
      14,    0,   84,    2, 0x0a /* Public */,
      15,    0,   85,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,   11,   12,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void PMD::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        PMD *_t = static_cast<PMD *>(_o);
        switch (_id) {
        case 0: _t->changeValue((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->changeView(); break;
        case 2: _t->showinvalid(); break;
        case 3: _t->showgrid(); break;
        case 4: _t->backDefault(); break;
        case 5: _t->PMDConnect(); break;
        case 6: _t->PMDDisconnect(); break;
        case 7: _t->showLayer((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 8: _t->pmdauto(); break;
        case 9: _t->pmdtopview(); break;
        case 10: _t->pmdquadspoints(); break;
        default: ;
        }
    }
}

const QMetaObject PMD::staticMetaObject = {
    { &QGLWidget::staticMetaObject, qt_meta_stringdata_PMD.data,
      qt_meta_data_PMD,  qt_static_metacall, 0, 0}
};


const QMetaObject *PMD::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *PMD::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_PMD.stringdata))
        return static_cast<void*>(const_cast< PMD*>(this));
    return QGLWidget::qt_metacast(_clname);
}

int PMD::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QGLWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 11)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 11;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 11)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 11;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
