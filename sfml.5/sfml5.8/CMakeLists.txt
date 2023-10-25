add_executable(sfml5.8 main.cpp)

target_include_directories(sfml5.8 PRIVATE ${SFML_INCLUDE_DIR})
target_compile_features(sfml5.8 PUBLIC cxx_std_17)
target_compile_definitions(sfml5.8 PRIVATE SFML_STATIC)

target_link_libraries(sfml5.8 ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})