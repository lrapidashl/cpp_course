add_executable(sfml1.1 main.cpp)

include_directories(headers D:/CppDistro/MinGW/include/SFML)

set(CMAKE_BUILD_TYPE Release)

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/CMakeModules")
set(SFML_STATIC_LIBRARIES TRUE)
find_package(Freetype)
find_package(JPEG)
find_package(SFML 2 COMPONENTS graphics window system REQUIRED)
include_directories(${SFML_INCLUDE_DIR})
target_link_libraries(sfml1.1 ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})

target_compile_features(sfml1.1 PUBLIC cxx_std_17)
target_compile_definitions(sfml1.1 PRIVATE SFML_STATIC)