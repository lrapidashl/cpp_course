add_executable(sfml5.4 main.cpp)

target_include_directories(sfml5.4 PRIVATE ${SFML_INCLUDE_DIR})
target_compile_features(sfml5.4 PUBLIC cxx_std_17)
target_compile_definitions(sfml5.4 PRIVATE SFML_STATIC)

target_link_libraries(sfml5.4 ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})