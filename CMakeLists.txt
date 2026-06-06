cmake_minimum_required(VERSION 3.16)
project(EDIT-VIDEO-PRO-COMPOSITOR LANGUAGES CXX CUDA)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

# Versión
set(PROJECT_VERSION_MAJOR 0)
set(PROJECT_VERSION_MINOR 1)
set(PROJECT_VERSION_PATCH 0)

# Opciones
option(BUILD_WITH_CUDA "Build with CUDA support" ON)
option(BUILD_WITH_TESTS "Build tests" ON)
option(BUILD_PYTHON_BINDINGS "Build Python bindings" ON)

# Find packages
find_package(Qt5 COMPONENTS Core Gui OpenGL Widgets REQUIRED)
find_package(OpenGL REQUIRED)
find_package(OpenEXR REQUIRED)
find_package(OpenColorIO REQUIRED)
find_package(glm REQUIRED)

if(BUILD_WITH_CUDA)
    find_package(CUDA REQUIRED)
    set(CUDA_NVCC_FLAGS "${CUDA_NVCC_FLAGS} -std=c++17")
endif()

# Directorios
add_subdirectory(src)

if(BUILD_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()

if(BUILD_PYTHON_BINDINGS)
    add_subdirectory(python)
endif()

# Resumen
message(STATUS "=== EDIT-VIDEO-PRO Compositor ===")
message(STATUS "Version: ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}.${PROJECT_VERSION_PATCH}")
message(STATUS "CUDA Support: ${BUILD_WITH_CUDA}")
message(STATUS "Tests: ${BUILD_WITH_TESTS}")
message(STATUS "Python Bindings: ${BUILD_PYTHON_BINDINGS}")
message(STATUS "=====================================")
