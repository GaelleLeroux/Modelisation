/****************************************************************************
** Meta object code from reading C++ file 'myWindow.hpp'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.5)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../src/local/interface/myWindow.hpp"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'myWindow.hpp' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.5. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_myWindow_t {
    QByteArrayData data[20];
    char stringdata0[332];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_myWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_myWindow_t qt_meta_stringdata_myWindow = {
    {
QT_MOC_LITERAL(0, 0, 8), // "myWindow"
QT_MOC_LITERAL(1, 9, 11), // "action_quit"
QT_MOC_LITERAL(2, 21, 0), // ""
QT_MOC_LITERAL(3, 22, 11), // "action_draw"
QT_MOC_LITERAL(4, 34, 16), // "action_wireframe"
QT_MOC_LITERAL(5, 51, 13), // "action_u_back"
QT_MOC_LITERAL(6, 65, 14), // "action_u_front"
QT_MOC_LITERAL(7, 80, 13), // "action_v_back"
QT_MOC_LITERAL(8, 94, 14), // "action_v_front"
QT_MOC_LITERAL(9, 109, 22), // "action_u_back_negative"
QT_MOC_LITERAL(10, 132, 23), // "action_u_front_negative"
QT_MOC_LITERAL(11, 156, 22), // "action_v_back_negative"
QT_MOC_LITERAL(12, 179, 23), // "action_v_front_negative"
QT_MOC_LITERAL(13, 203, 27), // "action_duplicate_boundaries"
QT_MOC_LITERAL(14, 231, 16), // "action_save_grid"
QT_MOC_LITERAL(15, 248, 16), // "action_load_grid"
QT_MOC_LITERAL(16, 265, 18), // "action_color_patch"
QT_MOC_LITERAL(17, 284, 14), // "action_surface"
QT_MOC_LITERAL(18, 299, 11), // "action_grid"
QT_MOC_LITERAL(19, 311, 20) // "action_grid_position"

    },
    "myWindow\0action_quit\0\0action_draw\0"
    "action_wireframe\0action_u_back\0"
    "action_u_front\0action_v_back\0"
    "action_v_front\0action_u_back_negative\0"
    "action_u_front_negative\0action_v_back_negative\0"
    "action_v_front_negative\0"
    "action_duplicate_boundaries\0"
    "action_save_grid\0action_load_grid\0"
    "action_color_patch\0action_surface\0"
    "action_grid\0action_grid_position"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_myWindow[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      18,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,  104,    2, 0x08 /* Private */,
       3,    0,  105,    2, 0x08 /* Private */,
       4,    0,  106,    2, 0x08 /* Private */,
       5,    0,  107,    2, 0x08 /* Private */,
       6,    0,  108,    2, 0x08 /* Private */,
       7,    0,  109,    2, 0x08 /* Private */,
       8,    0,  110,    2, 0x08 /* Private */,
       9,    0,  111,    2, 0x08 /* Private */,
      10,    0,  112,    2, 0x08 /* Private */,
      11,    0,  113,    2, 0x08 /* Private */,
      12,    0,  114,    2, 0x08 /* Private */,
      13,    0,  115,    2, 0x08 /* Private */,
      14,    0,  116,    2, 0x08 /* Private */,
      15,    0,  117,    2, 0x08 /* Private */,
      16,    0,  118,    2, 0x08 /* Private */,
      17,    0,  119,    2, 0x08 /* Private */,
      18,    0,  120,    2, 0x08 /* Private */,
      19,    0,  121,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void myWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        myWindow *_t = static_cast<myWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->action_quit(); break;
        case 1: _t->action_draw(); break;
        case 2: _t->action_wireframe(); break;
        case 3: _t->action_u_back(); break;
        case 4: _t->action_u_front(); break;
        case 5: _t->action_v_back(); break;
        case 6: _t->action_v_front(); break;
        case 7: _t->action_u_back_negative(); break;
        case 8: _t->action_u_front_negative(); break;
        case 9: _t->action_v_back_negative(); break;
        case 10: _t->action_v_front_negative(); break;
        case 11: _t->action_duplicate_boundaries(); break;
        case 12: _t->action_save_grid(); break;
        case 13: _t->action_load_grid(); break;
        case 14: _t->action_color_patch(); break;
        case 15: _t->action_surface(); break;
        case 16: _t->action_grid(); break;
        case 17: _t->action_grid_position(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject myWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_myWindow.data,
      qt_meta_data_myWindow,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *myWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *myWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_myWindow.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int myWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 18)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 18;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 18)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 18;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
