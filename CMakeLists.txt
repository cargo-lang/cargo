cmake_minimum_required(VERSION 3.15)
project(Cargo VERSION 1.0.0)

file(GLOB SOURCES "src/*.cpp")

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

# Directory for easier includes
list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

# Registers build options that are exposed to cmake
include(CMakeOptions.txt)

# Include CMake Modules
include(GNUInstallDirs)
include(PackConfigurations)
include(CompilerFlags)

# Include directories
include_directories(${CMAKE_SOURCE_DIR}/include)

add_executable(${PROJECT_NAME} ${SOURCES})

set_target_properties(${PROJECT_NAME} PROPERTIES VERSION ${PROJECT_VERSION})
