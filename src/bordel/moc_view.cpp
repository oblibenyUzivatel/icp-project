/****************************************************************************
** Meta object code from reading C++ file 'view.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.10.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../view.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'view.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.10.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_View_t {
    QByteArrayData data[15];
    char stringdata0[130];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_View_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_View_t qt_meta_stringdata_View = {
    {
QT_MOC_LITERAL(0, 0, 4), // "View"
QT_MOC_LITERAL(1, 5, 14), // "sigCreateBlock"
QT_MOC_LITERAL(2, 20, 0), // ""
QT_MOC_LITERAL(3, 21, 9), // "BlockType"
QT_MOC_LITERAL(4, 31, 4), // "type"
QT_MOC_LITERAL(5, 36, 5), // "long&"
QT_MOC_LITERAL(6, 42, 3), // "key"
QT_MOC_LITERAL(7, 46, 14), // "sigDeleteBlock"
QT_MOC_LITERAL(8, 61, 13), // "sigCreateWire"
QT_MOC_LITERAL(9, 75, 6), // "PortID"
QT_MOC_LITERAL(10, 82, 8), // "startkey"
QT_MOC_LITERAL(11, 91, 6), // "endkey"
QT_MOC_LITERAL(12, 98, 2), // "id"
QT_MOC_LITERAL(13, 101, 13), // "sigDeleteWire"
QT_MOC_LITERAL(14, 115, 14) // "slotDeleteWire"

    },
    "View\0sigCreateBlock\0\0BlockType\0type\0"
    "long&\0key\0sigDeleteBlock\0sigCreateWire\0"
    "PortID\0startkey\0endkey\0id\0sigDeleteWire\0"
    "slotDeleteWire"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_View[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,   39,    2, 0x06 /* Public */,
       7,    1,   44,    2, 0x06 /* Public */,
       8,    3,   47,    2, 0x06 /* Public */,
      13,    1,   54,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      14,    1,   57,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3, 0x80000000 | 5,    4,    6,
    QMetaType::Void, QMetaType::Long,    6,
    QMetaType::Void, 0x80000000 | 9, 0x80000000 | 9, 0x80000000 | 5,   10,   11,   12,
    QMetaType::Void, QMetaType::Long,    6,

 // slots: parameters
    QMetaType::Void, QMetaType::Long,    6,

       0        // eod
};

void View::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        View *_t = static_cast<View *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->sigCreateBlock((*reinterpret_cast< BlockType(*)>(_a[1])),(*reinterpret_cast< long(*)>(_a[2]))); break;
        case 1: _t->sigDeleteBlock((*reinterpret_cast< long(*)>(_a[1]))); break;
        case 2: _t->sigCreateWire((*reinterpret_cast< PortID(*)>(_a[1])),(*reinterpret_cast< PortID(*)>(_a[2])),(*reinterpret_cast< long(*)>(_a[3]))); break;
        case 3: _t->sigDeleteWire((*reinterpret_cast< long(*)>(_a[1]))); break;
        case 4: _t->slotDeleteWire((*reinterpret_cast< long(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            typedef void (View::*_t)(BlockType , long & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&View::sigCreateBlock)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (View::*_t)(long );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&View::sigDeleteBlock)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (View::*_t)(PortID , PortID , long & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&View::sigCreateWire)) {
                *result = 2;
                return;
            }
        }
        {
            typedef void (View::*_t)(long );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&View::sigDeleteWire)) {
                *result = 3;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject View::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_View.data,
      qt_meta_data_View,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *View::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *View::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_View.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int View::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 5;
    }
    return _id;
}

// SIGNAL 0
void View::sigCreateBlock(BlockType _t1, long & _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void View::sigDeleteBlock(long _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void View::sigCreateWire(PortID _t1, PortID _t2, long & _t3)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void View::sigDeleteWire(long _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
