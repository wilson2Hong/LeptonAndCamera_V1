/****************************************************************************
** Meta object code from reading C++ file 'leptonandcamera.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.7)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../leptonandcamera.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'leptonandcamera.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.7. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_LeptonAndCamera[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      16,   29,   29,   29, 0x08,
      30,   29,   29,   29, 0x08,
      42,   29,   29,   29, 0x08,
      56,   29,   29,   29, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_LeptonAndCamera[] = {
    "LeptonAndCamera\0openCamara()\0\0readFarme()\0"
    "closeCamara()\0takingPictures()\0"
};

void LeptonAndCamera::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        LeptonAndCamera *_t = static_cast<LeptonAndCamera *>(_o);
        switch (_id) {
        case 0: _t->openCamara(); break;
        case 1: _t->readFarme(); break;
        case 2: _t->closeCamara(); break;
        case 3: _t->takingPictures(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObjectExtraData LeptonAndCamera::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject LeptonAndCamera::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_LeptonAndCamera,
      qt_meta_data_LeptonAndCamera, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &LeptonAndCamera::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *LeptonAndCamera::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *LeptonAndCamera::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_LeptonAndCamera))
        return static_cast<void*>(const_cast< LeptonAndCamera*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int LeptonAndCamera::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
