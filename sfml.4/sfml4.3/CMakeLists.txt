add_executable(sfml4.3 main.cpp)

target_include_directories(sfml4.3 PRIVATE ${SFML_INCLUDE_DIR})
target_compile_features(sfml4.3 PUBLIC cxx_std_17)
target_compile_definitions(sfml4.3 PRIVATE SFML_STATIC)

target_link_libraries(sfml4.3 ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})