/****************************************************************************
** Meta object code from reading C++ file 'editorpage.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.5.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../editorpage.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'editorpage.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.5.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_EditorPage_t {
    QByteArrayData data[7];
    char stringdata0[69];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_EditorPage_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_EditorPage_t qt_meta_stringdata_EditorPage = {
    {
QT_MOC_LITERAL(0, 0, 10), // "EditorPage"
QT_MOC_LITERAL(1, 11, 3), // "pos"
QT_MOC_LITERAL(2, 15, 4), // "size"
QT_MOC_LITERAL(3, 20, 9), // "BackColor"
QT_MOC_LITERAL(4, 30, 10), // "FrameColor"
QT_MOC_LITERAL(5, 41, 10), // "FrameWidth"
QT_MOC_LITERAL(6, 52, 16) // "BackgroundPixmap"

    },
    "EditorPage\0pos\0size\0BackColor\0FrameColor\0"
    "FrameWidth\0BackgroundPixmap"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_EditorPage[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       6,   14, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // properties: name, type, flags
       1, QMetaType::QPointF, 0x00095103,
       2, QMetaType::QSizeF, 0x00095103,
       3, QMetaType::QColor, 0x00095103,
       4, QMetaType::QColor, 0x00095103,
       5, QMetaType::Int, 0x00095103,
       6, QMetaType::QString, 0x00095103,

       0        // eod
};

void EditorPage::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{

#ifndef QT_NO_PROPERTIES
    if (_c == QMetaObject::ReadProperty) {
        EditorPage *_t = static_cast<EditorPage *>(_o);
        Q_UNUSED(_t)
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< QPointF*>(_v) = _t->pos(); break;
        case 1: *reinterpret_cast< QSizeF*>(_v) = _t->getSize(); break;
        case 2: *reinterpret_cast< QColor*>(_v) = _t->backColor(); break;
        case 3: *reinterpret_cast< QColor*>(_v) = _t->frameColor(); break;
        case 4: *reinterpret_cast< int*>(_v) = _t->frameWidth(); break;
        case 5: *reinterpret_cast< QString*>(_v) = _t->getBackgroundPixmap(); break;
        default: break;
        }
    } else if (_c == QMetaObject::WriteProperty) {
        EditorPage *_t = static_cast<EditorPage *>(_o);
        Q_UNUSED(_t)
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->setPos(*reinterpret_cast< QPointF*>(_v)); break;
        case 1: _t->setSize(*reinterpret_cast< QSizeF*>(_v)); break;
        case 2: _t->setBackColor(*reinterpret_cast< QColor*>(_v)); break;
        case 3: _t->setFrameColor(*reinterpret_cast< QColor*>(_v)); break;
        case 4: _t->setFrameWidth(*reinterpret_cast< int*>(_v)); break;
        case 5: _t->setBackgroundPixmap(*reinterpret_cast< QString*>(_v)); break;
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

const QMetaObject EditorPage::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_EditorPage.data,
      qt_meta_data_EditorPage,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *EditorPage::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *EditorPage::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_EditorPage.stringdata0))
        return static_cast<void*>(const_cast< EditorPage*>(this));
    if (!strcmp(_clname, "QGraphicsItemGroup"))
        return static_cast< QGraphicsItemGroup*>(const_cast< EditorPage*>(this));
    return QObject::qt_metacast(_clname);
}

int EditorPage::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    
#ifndef QT_NO_PROPERTIES
   if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    } else if (_c == QMetaObject::QueryPropertyDesignable) {
        _id -= 6;
    } else if (_c == QMetaObject::QueryPropertyScriptable) {
        _id -= 6;
    } else if (_c == QMetaObject::QueryPropertyStored) {
        _id -= 6;
    } else if (_c == QMetaObject::QueryPropertyEditable) {
        _id -= 6;
    } else if (_c == QMetaObject::QueryPropertyUser) {
        _id -= 6;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}
QT_END_MOC_NAMESPACE
