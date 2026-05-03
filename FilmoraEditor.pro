QT += core gui widgets multimedia network sql concurrent

CONFIG += c++17

TARGET = FilmoraEditor
TEMPLATE = app

SOURCES += \
    src/main.cpp \
    src/mainwindow.cpp \
    src/videotimeline.cpp \
    src/videoeditor.cpp \
    src/paymentmanager.cpp \
    src/subscriptionmanager.cpp \
    src/effectsmanager.cpp \
    src/imagemanager.cpp \
    src/colorgradingmanager.cpp \
    src/titlesmanager.cpp \
    src/audiomanager.cpp \
    src/exportmanager.cpp \
    src/database.cpp

HEADERS += \
    src/mainwindow.h \
    src/videotimeline.h \
    src/videoeditor.h \
    src/paymentmanager.h \
    src/subscriptionmanager.h \
    src/effectsmanager.h \
    src/imagemanager.h \
    src/colorgradingmanager.h \
    src/titlesmanager.h \
    src/audiomanager.h \
    src/exportmanager.h \
    src/database.h

RESOURCES += resources.qrc

# Flags de compilación
win32 {
    QMAKE_CXXFLAGS += /std:c++17
    CONFIG += windows console
}

unix {
    QMAKE_CXXFLAGS += -std=c++17
}

# Output directories
CONFIG(debug, debug|release) {
    DESTDIR = $$PWD/build/debug
    OBJECTS_DIR = $$PWD/build/debug/obj
    MOC_DIR = $$PWD/build/debug/moc
    RCC_DIR = $$PWD/build/debug/rcc
} else {
    DESTDIR = $$PWD/build/release
    OBJECTS_DIR = $$PWD/build/release/obj
    MOC_DIR = $$PWD/build/release/moc
    RCC_DIR = $$PWD/build/release/rcc
}

# FFmpeg
INCLUDEPATH += C:/ffmpeg/include
LIBS += -LC:/ffmpeg/lib -lavcodec -lavformat -lavutil -lswscale
