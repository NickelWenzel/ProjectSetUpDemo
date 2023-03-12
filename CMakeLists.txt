cmake_minimum_required(VERSION 3.14)

project("ProjectSetUpDemo")

add_subdirectory(lib)

enable_testing()
add_subdirectory(test)