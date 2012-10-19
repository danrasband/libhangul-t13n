cmake_minimum_required(VERSION 2.8)
project(libhangeul-romaja C)

enable_testing()

# Add source files
add_subdirectory(src lib)
add_subdirectory(test)
