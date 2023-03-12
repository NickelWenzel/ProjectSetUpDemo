find_package(Catch2 REQUIRED CONFIG)

add_executable(smoke_test smoketest.cpp)

target_link_libraries(smoke_test PRIVATE
  testlib
  Catch2::Catch2WithMain)

add_test(NAME smoke_test COMMAND smoke_test)