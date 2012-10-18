cmake_minimum_required (VERSION 2.8)
project (LIBHANGEUL_ROMAJA)

# Add source files
add_subdirectory (src lib)

enable_testing()

# Add tests
add_test(yale yale WORKING_DIRECTORY test)
