cmake_minimum_required (VERSION 2.8)
project (LIBHANGEUL_ROMAJA)

MESSAGE(/home/danrasband/src/github/danrasband/libhangeul-romaja/src)
MESSAGE(/home/danrasband/src/github/danrasband/libhangeul-romaja/build)
include_directories(/home/danrasband/src/github/danrasband/libhangeul-romaja/src)
link_directories(/home/danrasband/src/github/danrasband/libhangeul-romaja/build/lib)

add_executable(yale yale.c)
target_link_libraries(yale hangeul-romaja)
