cmake_minimum_required(VERSION 3.14)

project("ProjectSetUpDemo")

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib/$<CONFIG>)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/$<CONFIG>)

add_subdirectory(lib)

enable_testing()
add_subdirectory(test)