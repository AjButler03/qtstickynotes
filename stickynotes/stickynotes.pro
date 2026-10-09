TEMPLATE = app
TARGET = name_of_the_app

QT = core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

SOURCES += \
    main.cpp \
    note.cpp \
    noteheader.cpp

HEADERS += \
    doubleclicklabel.h \
    note.h \
    noteheader.h
