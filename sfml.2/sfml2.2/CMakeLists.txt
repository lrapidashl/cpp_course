add_executable(sfml2.2 main.cpp)

include_directories(headers ../../included/SFML)

set(CMAKE_BUILD_TYPE Release)

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/CMakeModules")
set(SFML_STATIC_LIBRARIES TRUE)
find_package(Freetype)
find_package(JPEG)
find_package(SFML 2 COMPONENTS graphics window system REQUIRED)
include_directories(${SFML_INCLUDE_DIR})
target_link_libraries(sfml2.2 ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})

target_compile_features(sfml2.2 PUBLIC cxx_std_17)
target_compile_definitions(sfml2.2 PRIVATE SFML_STATIC)