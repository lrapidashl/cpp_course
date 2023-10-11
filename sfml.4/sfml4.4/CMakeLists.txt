add_executable(sfml4.4 main.cpp)

target_include_directories(sfml4.4 PRIVATE ${SFML_INCLUDE_DIR})
target_compile_features(sfml4.4 PUBLIC cxx_std_17)
target_compile_definitions(sfml4.4 PRIVATE SFML_STATIC)

target_link_libraries(sfml4.4 ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})