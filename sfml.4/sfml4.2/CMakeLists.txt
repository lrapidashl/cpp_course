add_executable(sfml4.2 main.cpp)

target_include_directories(sfml4.2 PRIVATE ${SFML_INCLUDE_DIR})
target_compile_features(sfml4.2 PUBLIC cxx_std_17)
target_compile_definitions(sfml4.2 PRIVATE SFML_STATIC)

target_link_libraries(sfml4.2 ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})