cmake_minimum_required(VERSION 3.8 FATAL_ERROR)

project(sfml-lab-4)

include_directories(headers ../included/SFML)

set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/CMakeModules")
set(SFML_STATIC_LIBRARIES TRUE)

find_package(Freetype REQUIRED)
find_package(JPEG REQUIRED)
find_package(SFML 2 COMPONENTS window graphics system REQUIRED)
include_directories(${SFML_INCLUDE_DIR})

add_subdirectory(sfml4.1)
add_subdirectory(sfml4.2)
add_subdirectory(sfml4.3)
add_subdirectory(sfml4.4)