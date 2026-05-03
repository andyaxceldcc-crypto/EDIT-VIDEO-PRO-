cmake_minimum_required(VERSION 3.16)
project(FilmoraEditor)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt6 COMPONENTS 
    Core 
    Gui 
    Widgets 
    Multimedia 
    Network 
    Sql 
    Concurrent
    Core5Compat
    REQUIRED
)

find_package(FFmpeg REQUIRED)

set(SOURCES
    src/main.cpp
    src/mainwindow.h
    src/mainwindow.cpp
    src/videotimeline.h
    src/videotimeline.cpp
    src/videoeditor.h
    src/videoeditor.cpp
    src/paymentmanager.h
    src/paymentmanager.cpp
    src/subscriptionmanager.h
    src/subscriptionmanager.cpp
    src/effectsmanager.h
    src/effectsmanager.cpp
    src/imagemanager.h
    src/imagemanager.cpp
    src/colorgradingmanager.h
    src/colorgradingmanager.cpp
    src/titlesmanager.h
    src/titlesmanager.cpp
    src/audiomanager.h
    src/audiomanager.cpp
    src/exportmanager.h
    src/exportmanager.cpp
    src/database.h
    src/database.cpp
)

add_executable(FilmoraEditor ${SOURCES} resources.qrc)

target_link_libraries(FilmoraEditor
    Qt6::Core
    Qt6::Gui
    Qt6::Widgets
    Qt6::Multimedia
    Qt6::Network
    Qt6::Sql
    Qt6::Concurrent
    ${FFMPEG_LIBRARIES}
)

target_include_directories(FilmoraEditor PRIVATE ${FFMPEG_INCLUDE_DIRS})
