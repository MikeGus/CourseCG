/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../mainwindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_MainWindow_t {
    QByteArrayData data[20];
    char stringdata0[354];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MainWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MainWindow_t qt_meta_stringdata_MainWindow = {
    {
QT_MOC_LITERAL(0, 0, 10), // "MainWindow"
QT_MOC_LITERAL(1, 11, 23), // "on_actionInfo_triggered"
QT_MOC_LITERAL(2, 35, 0), // ""
QT_MOC_LITERAL(3, 36, 22), // "on_btnAddPrism_clicked"
QT_MOC_LITERAL(4, 59, 22), // "on_btnDelPrism_clicked"
QT_MOC_LITERAL(5, 82, 22), // "on_btnAddLight_clicked"
QT_MOC_LITERAL(6, 105, 22), // "on_btnDelLight_clicked"
QT_MOC_LITERAL(7, 128, 8), // "addPrism"
QT_MOC_LITERAL(8, 137, 6), // "Prism&"
QT_MOC_LITERAL(9, 144, 5), // "prism"
QT_MOC_LITERAL(10, 150, 13), // "keyPressEvent"
QT_MOC_LITERAL(11, 164, 10), // "QKeyEvent*"
QT_MOC_LITERAL(12, 175, 31), // "on_listWidget_currentRowChanged"
QT_MOC_LITERAL(13, 207, 10), // "currentRow"
QT_MOC_LITERAL(14, 218, 33), // "on_listWidget_2_currentRowCha..."
QT_MOC_LITERAL(15, 252, 21), // "on_listWidget_pressed"
QT_MOC_LITERAL(16, 274, 23), // "on_listWidget_2_pressed"
QT_MOC_LITERAL(17, 298, 22), // "on_radioButton_toggled"
QT_MOC_LITERAL(18, 321, 7), // "checked"
QT_MOC_LITERAL(19, 329, 24) // "on_radioButton_2_toggled"

    },
    "MainWindow\0on_actionInfo_triggered\0\0"
    "on_btnAddPrism_clicked\0on_btnDelPrism_clicked\0"
    "on_btnAddLight_clicked\0on_btnDelLight_clicked\0"
    "addPrism\0Prism&\0prism\0keyPressEvent\0"
    "QKeyEvent*\0on_listWidget_currentRowChanged\0"
    "currentRow\0on_listWidget_2_currentRowChanged\0"
    "on_listWidget_pressed\0on_listWidget_2_pressed\0"
    "on_radioButton_toggled\0checked\0"
    "on_radioButton_2_toggled"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainWindow[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      13,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   79,    2, 0x08 /* Private */,
       3,    0,   80,    2, 0x08 /* Private */,
       4,    0,   81,    2, 0x08 /* Private */,
       5,    0,   82,    2, 0x08 /* Private */,
       6,    0,   83,    2, 0x08 /* Private */,
       7,    1,   84,    2, 0x08 /* Private */,
      10,    1,   87,    2, 0x08 /* Private */,
      12,    1,   90,    2, 0x08 /* Private */,
      14,    1,   93,    2, 0x08 /* Private */,
      15,    1,   96,    2, 0x08 /* Private */,
      16,    1,   99,    2, 0x08 /* Private */,
      17,    1,  102,    2, 0x08 /* Private */,
      19,    1,  105,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 8,    9,
    QMetaType::Void, 0x80000000 | 11,    2,
    QMetaType::Void, QMetaType::Int,   13,
    QMetaType::Void, QMetaType::Int,   13,
    QMetaType::Void, QMetaType::QModelIndex,    2,
    QMetaType::Void, QMetaType::QModelIndex,    2,
    QMetaType::Void, QMetaType::Bool,   18,
    QMetaType::Void, QMetaType::Bool,   18,

       0        // eod
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        MainWindow *_t = static_cast<MainWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->on_actionInfo_triggered(); break;
        case 1: _t->on_btnAddPrism_clicked(); break;
        case 2: _t->on_btnDelPrism_clicked(); break;
        case 3: _t->on_btnAddLight_clicked(); break;
        case 4: _t->on_btnDelLight_clicked(); break;
        case 5: _t->addPrism((*reinterpret_cast< Prism(*)>(_a[1]))); break;
        case 6: _t->keyPressEvent((*reinterpret_cast< QKeyEvent*(*)>(_a[1]))); break;
        case 7: _t->on_listWidget_currentRowChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 8: _t->on_listWidget_2_currentRowChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 9: _t->on_listWidget_pressed((*reinterpret_cast< const QModelIndex(*)>(_a[1]))); break;
        case 10: _t->on_listWidget_2_pressed((*reinterpret_cast< const QModelIndex(*)>(_a[1]))); break;
        case 11: _t->on_radioButton_toggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 12: _t->on_radioButton_2_toggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject MainWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_MainWindow.data,
      qt_meta_data_MainWindow,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow.stringdata0))
        return static_cast<void*>(const_cast< MainWindow*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 13)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 13;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 13)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 13;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
