/****************************************************************************
** Meta object code from reading C++ file 'zsfilesystemwatcher.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.2.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../ZeroSyncDesktop/zsfilesystemwatcher.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'zsfilesystemwatcher.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.2.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_ZSFileSystemWatcher_t {
    QByteArrayData data[6];
    char stringdata[118];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    offsetof(qt_meta_stringdata_ZSFileSystemWatcher_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData) \
    )
static const qt_meta_stringdata_ZSFileSystemWatcher_t qt_meta_stringdata_ZSFileSystemWatcher = {
    {
QT_MOC_LITERAL(0, 0, 19),
QT_MOC_LITERAL(1, 20, 31),
QT_MOC_LITERAL(2, 52, 0),
QT_MOC_LITERAL(3, 53, 26),
QT_MOC_LITERAL(4, 80, 20),
QT_MOC_LITERAL(5, 101, 15)
    },
    "ZSFileSystemWatcher\0signalDirectoryChangeRecognized\0"
    "\0signalFileChangeRecognized\0"
    "slotDirectoryChanged\0slotFileChanged\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ZSFileSystemWatcher[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   34,    2, 0x06,
       3,    1,   37,    2, 0x06,

 // slots: name, argc, parameters, tag, flags
       4,    1,   40,    2, 0x08,
       5,    1,   43,    2, 0x08,

 // signals: parameters
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void, QMetaType::QString,    2,

 // slots: parameters
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void, QMetaType::QString,    2,

       0        // eod
};

void ZSFileSystemWatcher::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        ZSFileSystemWatcher *_t = static_cast<ZSFileSystemWatcher *>(_o);
        switch (_id) {
        case 0: _t->signalDirectoryChangeRecognized((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: _t->signalFileChangeRecognized((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 2: _t->slotDirectoryChanged((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 3: _t->slotFileChanged((*reinterpret_cast< QString(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (ZSFileSystemWatcher::*_t)(QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ZSFileSystemWatcher::signalDirectoryChangeRecognized)) {
                *result = 0;
            }
        }
        {
            typedef void (ZSFileSystemWatcher::*_t)(QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ZSFileSystemWatcher::signalFileChangeRecognized)) {
                *result = 1;
            }
        }
    }
}

const QMetaObject ZSFileSystemWatcher::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_ZSFileSystemWatcher.data,
      qt_meta_data_ZSFileSystemWatcher,  qt_static_metacall, 0, 0}
};


const QMetaObject *ZSFileSystemWatcher::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ZSFileSystemWatcher::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ZSFileSystemWatcher.stringdata))
        return static_cast<void*>(const_cast< ZSFileSystemWatcher*>(this));
    return QObject::qt_metacast(_clname);
}

int ZSFileSystemWatcher::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 4)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 4;
    }
    return _id;
}

// SIGNAL 0
void ZSFileSystemWatcher::signalDirectoryChangeRecognized(QString _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void ZSFileSystemWatcher::signalFileChangeRecognized(QString _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_END_MOC_NAMESPACE
