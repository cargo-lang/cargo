cmake_minimum_required(VERSION 3.15)
project(Cargo VERSION 1.0.0 LANGUAGES CXX)

file(GLOB SOURCES "src/*.cpp")

# Directory for easier includes
list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

# Registers build options that are exposed to cmake
include(CMakeOptions.txt)

# Include CMake Modules
include(InstallConfigurations)
include(PackConfigurations)

add_library(${PROJECT_NAME}42 SHARED ${SOURCES})

if (WIN32)
  add_executable(${PROJECT_NAME} src/main.cpp)
else()
  add_executable(${PROJECT_NAME} src/main.cpp)
endif()

target_link_libraries(${PROJECT_NAME} PRIVATE ${PROJECT_NAME}42)

# Include directories
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/include)
