add_library(testlib SHARED)
add_library(testlib::testlib ALIAS testlib)
target_sources(testlib
  PRIVATE
    src/testlib.cpp
  PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/testlib/testlib.hpp>
    $<INSTALL_INTERFACE:include/testlib/testlib.hpp>
)

include(GenerateExportHeader)
generate_export_header(testlib EXPORT_FILE_NAME include/testlib/export.hpp)

target_include_directories(testlib PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/include>
  $<INSTALL_INTERFACE:include>
)

find_package(fmt REQUIRED CONFIG)
target_link_libraries(testlib PRIVATE fmt::fmt)

include(GNUInstallDirs)
install(TARGETS testlib EXPORT testlibTargets)
install(DIRECTORY include/ DESTINATION include)
install(EXPORT testlibTargets
  DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/testlib
  NAMESPACE testlib::)