QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    src/Fractals/Fractal.cpp \
    src/Fractals/burningship.cpp \
    main.cpp \
    src/Fractals/mandelbrot.cpp \
    src/Fractals/tricorn.cpp \
    src/widget.cpp

HEADERS += \
    src/Fractals/AbstractFractal.h \
    src/Fractals/Fractal.h \
    src/Fractals/burningship.h \
    src/Fractals/coordinates.h \
    src/Fractals/mandelbrot.h \
    src/tricorn.h \
    src/widget.h

FORMS += \
    src/widget.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
