#-------------------------------------------------
#
# Project created by QtCreator 2013-07-12T14:10:56
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = mycom_3
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    win_qextserialport.cpp \
    qextserialport.cpp \
    qextserialbase.cpp \
    aboutdialog.cpp

HEADERS  += mainwindow.h \
    win_qextserialport.h \
    qextserialport.h \
    qextserialbase.h \
    aboutdialog.h

FORMS    += mainwindow.ui \
    aboutdialog.ui

RESOURCES += \
    images.qrc

RC_FILE += ico.rc

OTHER_FILES += \
    ico.rc
