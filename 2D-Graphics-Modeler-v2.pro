QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    contact.cpp \
    main.cpp \
    mainwindow.cpp \
    renderarea.cpp \
    secdialog.cpp

HEADERS += \
    contact.h \
    mainwindow.h \
    renderarea.h \
    secdialog.h \
    shapes.h \
    ui_contact.h \
    ui_mainwindow.h \
    ui_secdialog.h \
    vector.h

FORMS += \
    contact.ui \
    mainwindow.ui \
    secdialog.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

SUBDIRS += \
    2D-Graphics-Modeler.pro

DISTFILES += \
    .qmake.stash \
    2D-Graphics-Modeler-v2.pro.user \
    2D-Graphics-Modeler.pro.user \
    2D-Graphics-Modeler.pro.user.a8bac56 \
    Makefile \
    Makefile.Debug \
    Makefile.Release \
    README.md \
    object_script.2D-Graphics-Modeler.Debug \
    object_script.2D-Graphics-Modeler.Release \
    scrumtest \
    shape_input_file_specs.txt \
    shapes.txt
