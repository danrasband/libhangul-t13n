include_directories(${libhangeul-romaja_SOURCE_DIR}/src)
link_directories(${libhangeul-romaja_BINARY_DIR}/lib)

add_executable(hangeulconv hangeulconv.c)
target_link_libraries(hangeulconv hangeul-romaja)

install(PROGRAMS ${CMAKE_CURRENT_BINARY_DIR}/hangeulconv DESTINATION bin)
