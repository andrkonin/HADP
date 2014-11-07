/****************************************************************************
** Meta object code from reading C++ file 'dialog.h'
**
** Created: Tue Jun 16 10:49:56 2009
**      by: The Qt Meta Object Compiler version 61 (Qt 4.5.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "dialog.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'dialog.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 61
#error "This file was generated using the moc from 4.5.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_Dialog[] = {

 // content:
       2,       // revision
       0,       // classname
       0,    0, // classinfo
      12,   12, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors

 // slots: signature, parameters, type, tag, flags
       8,    7,    7,    7, 0x0a,
      19,    7,    7,    7, 0x0a,
      28,    7,    7,    7, 0x0a,
      38,    7,    7,    7, 0x0a,
      51,    7,    7,    7, 0x0a,
      67,    7,    7,    7, 0x0a,
      81,    7,    7,    7, 0x0a,
      91,    7,    7,    7, 0x0a,
     104,    7,    7,    7, 0x0a,
     121,    7,    7,    7, 0x0a,
     134,    7,    7,    7, 0x0a,
     146,    7,    7,    7, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_Dialog[] = {
    "Dialog\0\0sendData()\0manual()\0pmdAuto()\0"
    "pmdConnect()\0pmdDisconnect()\0backDefault()\0"
    "pmdStop()\0showvalues()\0updateColorBar()\0"
    "changeView()\0switchtop()\0switchquadspoints()\0"
};

const QMetaObject Dialog::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_Dialog,
      qt_meta_data_Dialog, 0 }
};

const QMetaObject *Dialog::metaObject() const
{
    return &staticMetaObject;
}

void *Dialog::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Dialog))
        return static_cast<void*>(const_cast< Dialog*>(this));
    return QDialog::qt_metacast(_clname);
}

int Dialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: sendData(); break;
        case 1: manual(); break;
        case 2: pmdAuto(); break;
        case 3: pmdConnect(); break;
        case 4: pmdDisconnect(); break;
        case 5: backDefault(); break;
        case 6: pmdStop(); break;
        case 7: showvalues(); break;
        case 8: updateColorBar(); break;
        case 9: changeView(); break;
        case 10: switchtop(); break;
        case 11: switchquadspoints(); break;
        default: ;
        }
        _id -= 12;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
