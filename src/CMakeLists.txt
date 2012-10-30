file(GLOB hangeul_romaja_srcs *.c)

add_library(hangeul-romaja SHARED ${hangeul_romaja_srcs})
add_library(hangeul-romaja_static STATIC ${hangeul_romaja_srcs})

if(APPLE)
	install(FILES ${CMAKE_CURRENT_BINARY_DIR}/libhangeul-romaja.dylib DESTINATION lib)
	install(FILES ${CMAKE_CURRENT_BINARY_DIR}/libhangeul-romaja_static.a DESTINATION lib)
elseif(UNIX)
	install(FILES ${CMAKE_CURRENT_BINARY_DIR}/libhangeul-romaja.so DESTINATION lib)
	install(FILES ${CMAKE_CURRENT_BINARY_DIR}/libhangeul-romaja_static.a DESTINATION lib)
endif()

INSTALL(FILES ${CMAKE_CURRENT_SOURCE_DIR}/hangeul-romaja.h DESTINATION include)
