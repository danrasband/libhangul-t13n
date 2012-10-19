add_library(hangeul-romaja SHARED hangeul-romaja.c)
add_library(hangeul-romaja_static STATIC hangeul-romaja.c)

target_link_libraries(hangeul-romaja hangul)
