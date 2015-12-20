/****************************************************************************
** Meta object code from reading C++ file 'itembase.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.5.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../itembase.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'itembase.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.5.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_ItemBase_t {
    QByteArrayData data[10];
    char stringdata0[80];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ItemBase_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ItemBase_t qt_meta_stringdata_ItemBase = {
    {
QT_MOC_LITERAL(0, 0, 8), // "ItemBase"
QT_MOC_LITERAL(1, 9, 7), // "opacity"
QT_MOC_LITERAL(2, 17, 7), // "enabled"
QT_MOC_LITERAL(3, 25, 7), // "visible"
QT_MOC_LITERAL(4, 33, 3), // "pos"
QT_MOC_LITERAL(5, 37, 4), // "size"
QT_MOC_LITERAL(6, 42, 1), // "z"
QT_MOC_LITERAL(7, 44, 8), // "rotation"
QT_MOC_LITERAL(8, 53, 5), // "scale"
QT_MOC_LITERAL(9, 59, 20) // "transformOriginPoint"

    },
    "ItemBase\0opacity\0enabled\0visible\0pos\0"
    "size\0z\0rotation\0scale\0transformOriginPoint"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ItemBase[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       9,   14, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // properties: name, type, flags
       1, QMetaType::QReal, 0x00095103,
       2, QMetaType::Bool, 0x00095103,
       3, QMetaType::Bool, 0x00095103,
       4, QMetaType::QPointF, 0x00095103,
       5, QMetaType::QSizeF, 0x00095103,
       6, QMetaType::QReal, 0x00095003,
       7, QMetaType::QReal, 0x00095103,
       8, QMetaType::QReal, 0x00095103,
       9, QMetaType::QPointF, 0x00095103,

       0        // eod
};

void ItemBase::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{

#ifndef QT_NO_PROPERTIES
    if (_c == QMetaObject::ReadProperty) {
        ItemBase *_t = static_cast<ItemBase *>(_o);
        Q_UNUSED(_t)
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< qreal*>(_v) = _t->opacity(); break;
        case 1: *reinterpret_cast< bool*>(_v) = _t->isEnabled(); break;
        case 2: *reinterpret_cast< bool*>(_v) = _t->getVisible(); break;
        case 3: *reinterpret_cast< QPointF*>(_v) = _t->pos(); break;
        case 4: *reinterpret_cast< QSizeF*>(_v) = _t->getSize(); break;
        case 5: *reinterpret_cast< qreal*>(_v) = _t->zValue(); break;
        case 6: *reinterpret_cast< qreal*>(_v) = _t->rotation(); break;
        case 7: *reinterpret_cast< qreal*>(_v) = _t->scale(); break;
        case 8: *reinterpret_cast< QPointF*>(_v) = _t->transformOriginPoint(); break;
        default: break;
        }
    } else if (_c == QMetaObject::WriteProperty) {
        ItemBase *_t = static_cast<ItemBase *>(_o);
        Q_UNUSED(_t)
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->setOpacity(*reinterpret_cast< qreal*>(_v)); break;
        case 1: _t->setEnabled(*reinterpret_cast< bool*>(_v)); break;
        case 2: _t->setVisible(*reinterpret_cast< bool*>(_v)); break;
        case 3: _t->setPos(*reinterpret_cast< QPointF*>(_v)); break;
        case 4: _t->setSize(*reinterpret_cast< QSizeF*>(_v)); break;
        case 5: _t->setZValue(*reinterpret_cast< qreal*>(_v)); break;
        case 6: _t->setRotation(*reinterpret_cast< qreal*>(_v)); break;
        case 7: _t->setScale(*reinterpret_cast< qreal*>(_v)); break;
        case 8: _t->setTransformOriginPoint(*reinterpret_cast< QPointF*>(_v)); break;
        default: break;
        }
    } else if (_c == QMetaObject::ResetProperty) {
    }
#endif // QT_NO_PROPERTIES
    Q_UNUSED(_o);
    Q_UNUSED(_id);
    Q_UNUSED(_c);
    Q_UNUSED(_a);
}

const QMetaObject ItemBase::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_ItemBase.data,
      qt_meta_data_ItemBase,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *ItemBase::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ItemBase::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_ItemBase.stringdata0))
        return static_cast<void*>(const_cast< ItemBase*>(this));
    if (!strcmp(_clname, "QGraphicsItem"))
        return static_cast< QGraphicsItem*>(const_cast< ItemBase*>(this));
    return QObject::qt_metacast(_clname);
}

int ItemBase::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    
#ifndef QT_NO_PROPERTIES
   if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    } else if (_c == QMetaObject::QueryPropertyDesignable) {
        _id -= 9;
    } else if (_c == QMetaObject::QueryPropertyScriptable) {
        _id -= 9;
    } else if (_c == QMetaObject::QueryPropertyStored) {
        _id -= 9;
    } else if (_c == QMetaObject::QueryPropertyEditable) {
        _id -= 9;
    } else if (_c == QMetaObject::QueryPropertyUser) {
        _id -= 9;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}
QT_END_MOC_NAMESPACE
