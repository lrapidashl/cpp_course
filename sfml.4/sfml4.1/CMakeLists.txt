add_executable(sfml4.1 main.cpp)

target_include_directories(sfml4.1 PRIVATE ${SFML_INCLUDE_DIR})
target_compile_features(sfml4.1 PUBLIC cxx_std_17)
target_compile_definitions(sfml4.1 PRIVATE SFML_STATIC)

target_link_libraries(sfml4.1 ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})