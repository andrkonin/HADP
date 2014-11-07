# -------------------------------------------------
# Project created by QtCreator 2009-06-05T14:29:58
# -------------------------------------------------
DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x000000
Qt += widgets
QT += network \
    opengl

TARGET = glpicture
TEMPLATE = app

INCLUDEPATH += C:/Users/kentand1/Desktop/Hyperion/simpleopengl/FirsttaskPMD
CONFIG      += debug_and_release
DEPENDPATH  += C:/Users/kentand1/Desktop/Hyperion/simpleopengl/FirsttaskPMD
LIBPATH     += C:/Users/kentand1/Desktop/Hyperion/simpleopengl/FirsttaskPMD

SOURCES += main.cpp \
    dialog.cpp \
    TOF_Sensor.cpp \
    pmd.cpp
HEADERS += dialog.h \
    pmdsdk2common.h \
    pmdsdk2.h \
    pmddatadescription.h \
    FORMS \
    += \
    dialog.ui \
    colorbar.h \
    pmd.h

LIBS        += \
     -LC:/Users/kentand1/Desktop/Hyperion/simpleopengl/FirsttaskPMD \
     -lpmdaccess2
