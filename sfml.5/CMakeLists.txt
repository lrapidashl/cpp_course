cmake_minimum_required(VERSION 3.8 FATAL_ERROR)

project(sfml-lab-5)

include_directories(headers ../included/SFML)

set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/CMakeModules")
set(SFML_STATIC_LIBRARIES TRUE)

find_package(Freetype REQUIRED)
find_package(JPEG REQUIRED)
find_package(SFML 2 COMPONENTS window graphics system REQUIRED)
include_directories(${SFML_INCLUDE_DIR})

add_subdirectory(sfml5.1)
add_subdirectory(sfml5.2)
add_subdirectory(sfml5.3)
add_subdirectory(sfml5.4)
add_subdirectory(sfml5.5)
add_subdirectory(sfml5.6)
add_subdirectory(sfml5.7)
add_subdirectory(sfml5.8)