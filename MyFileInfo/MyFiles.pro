#QMake file.

QT += gui core widgets

SOURCES += main.cc \
    TextWindow.cc \
    File.cc \
    MainWindow.cpp

HEADERS += \
    TextWindow.h \
    File.h \
    MainWindow.h

FORMS += MainWindow.ui
