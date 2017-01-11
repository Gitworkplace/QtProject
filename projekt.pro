#-------------------------------------------------
#
# Project created by QtCreator 2011-03-04T17:34:20
#
#-------------------------------------------------

TARGET = PhysicExample-07-CharacterController
QT       += gui core widgets opengl
TEMPLATE = app
CONFIG += c++11

win32 {
    CONFIG += console   #Notwendig in 5.5, da sonst qMain gesucht wird und nicht gefunden wird... eher ein Bug in Qt5.5?
    LIBS += -lopengl32  #Erzwingt Verwendung von Desktop OpenGL (sonst evtl. ES)
}
#Um GL ES3 Header zu finden
android {
    message("* Using settings for Android.")
    message($$ANDROID_PLATFORM_PATH)
    INCLUDEPATH += /Users/bdr1/AndroidDev/android-ndk-r11c/platforms/android-23/arch-arm/usr/include #$$ANDROID_PLATFORM_PATH/include
}

DEFINES += SRCDIR=\\\"$${_PRO_FILE_PWD_}\\\"

SGFRAMEWORKINCLUDEPATH = "$$PWD/SGFrameworkLib"
SGFRAMEWORKPATH = $${SGFRAMEWORKINCLUDEPATH}
INCLUDEPATH += $${SGFRAMEWORKINCLUDEPATH}
DEPENDPATH += $${SGFRAMEWORKINCLUDEPATH}

LIBS += -L$${SGFRAMEWORKPATH} -lSGFramework

win32:!win32-g++: PRE_TARGETDEPS += $${SGFRAMEWORKPATH}/SGFramework.lib
else:unix|win32-g++: PRE_TARGETDEPS += $${SGFRAMEWORKPATH}/libSGFramework.a



SOURCES += \
    characterticker.cpp \
    myscene.cpp \
    playerattributes.cpp \
    objticker.cpp \
    interface.cpp \
    sceneholder.cpp
HEADERS += \
    characterticker.h \
    trycallback.h \
    playerattributes.h \
    objticker.h \
    interface.h \
    sceneholder.h

DISTFILES += \
    texture.frag \
    zeug/Shader/player.frag \
    zeug/Shader/texture.frag \
    zeug/Shader/texture.vert \
    zeug/Shader/giftcountereiner.vert \
    zeug/Shader/giftcounterzehner.vert \
    zeug/Shader/herzinterface.vert \
    zeug/Shader/lebencounter.vert \
    zeug/Shader/Level.frag \
    zeug/Shader/Level.vert \


RESOURCES += \
    myshaders.qrc

