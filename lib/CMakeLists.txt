add_library(testlib SHARED)
add_library(testlib::testlib ALIAS testlib)
target_sources(testlib
  PRIVATE
    src/testlib.cpp
  PUBLIC
    include/testlib/testlib.hpp
)

include(GenerateExportHeader)
generate_export_header(testlib EXPORT_FILE_NAME include/testlib/export.hpp)

target_include_directories(testlib PUBLIC
  ${CMAKE_CURRENT_SOURCE_DIR}/include
  ${CMAKE_CURRENT_BINARY_DIR}/include
  "$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>"
)

find_package(fmt REQUIRED CONFIG)
target_link_libraries(testlib PRIVATE fmt::fmt)

install(TARGETS testlib)