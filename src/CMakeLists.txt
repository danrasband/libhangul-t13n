add_library(hangeul-romaja SHARED hangeul-romaja.c yale.c yale_original.c mccune_reischauer.c revised_romanization.c ipa.c)
add_library(hangeul-romaja_static STATIC hangeul-romaja.c yale.c yale_original.c mccune_reischauer.c revised_romanization.c ipa.c)

if(APPLE)
	install(FILES ${CMAKE_CURRENT_BINARY_DIR}/libhangeul-romaja.dylib DESTINATION lib)
	install(FILES ${CMAKE_CURRENT_BINARY_DIR}/libhangeul-romaja_static.a DESTINATION lib)
elseif(UNIX)
	install(FILES ${CMAKE_CURRENT_BINARY_DIR}/libhangeul-romaja.so DESTINATION lib)
	install(FILES ${CMAKE_CURRENT_BINARY_DIR}/libhangeul-romaja_static.a DESTINATION lib)
endif()

INSTALL(FILES ${CMAKE_CURRENT_SOURCE_DIR}/hangeul-romaja.h DESTINATION include)
