#-------------------------------------------------
#
# Project created by QtCreator 2019-12-16T18:27:13
#
#-------------------------------------------------

QT       += core gui
QT       *= xml opengl
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = fbxblendshape
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11
OBJECTS_DIR=$${PWD}/build


QGLVIEWER_INCLUDE_DIRS="D:\soft\libQGLViewer-2.7.1"
QGLVIEWER_LIBRARY_DIRS="D:\soft\libQGLViewer-2.7.1\QGLViewer"
TRIMESH_INCLUDE_DIRS="D:\soft\trimesh2\include"
TRIMESH_LIBRARY_DIRS="D:\soft\trimesh2\lib"
FBX_SDK_INCLUDE_DIRS="D:\Autodesk\FBX\FBX SDK\2019.0\include"
FBX_SDK_LIBRARY_DIRS="D:\Autodesk\FBX\FBX SDK\2019.0\lib\vs2015\x64\release"
ZLIB_INCLUDE_DIRS="D:\soft\opencv3\sources\3rdparty\zlib"
ZLIB_LIBRARY_DIRS="D:\soft\opencv3\build\3rdparty\lib\Release"
INCLUDEPATH+=$$QGLVIEWER_INCLUDE_DIRS
INCLUDEPATH+=D:\soft\eigen-eigen-323c052e1731
INCLUDEPATH+=$$TRIMESH_INCLUDE_DIRS
INCLUDEPATH+=$$FBX_SDK_INCLUDE_DIRS
INCLUDEPATH+=$$ZLIB_INCLUDE_DIRS

LIBS += -L$$QGLVIEWER_LIBRARY_DIRS -lQGLViewer2
LIBS += -L$$TRIMESH_LIBRARY_DIRS   -lgluit
LIBS += -L$$FBX_SDK_LIBRARY_DIRS -llibfbxsdk-md
LIBS += -L$$ZLIB_LIBRARY_DIRS -lzlib
SOURCES += \
        Common/Common.cxx \
        dialog.cpp \
        eigenmesh.cpp \
        fbxsdkfunctions.cpp \
        graphics/viewer.cpp \
        main.cpp \
        mainwindow.cpp \
        settings.cpp \
        src/cnpy.cpp \
        ui/treeitem.cpp \
        ui/treemodel.cpp

HEADERS += \
        Common/Common.h \
        dialog.h \
        eigenmesh.h \
        fbxsdkfunctions.h \
        graphics/viewer.h \
        mainwindow.h \
        settings.h \
        src/NumpyUtil.h \
        src/cnpy.h \
        ui/treeitem.h \
        ui/treemodel.h \
        ui_dialog.h \
        util/eigenfunctions.h

FORMS += \
        dialog.ui \
        mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    icon.qrc
