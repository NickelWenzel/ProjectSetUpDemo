#include<testlib/testlib.hpp>

#include<catch2/catch_test_macros.hpp>

#include <string>

TEST_CASE("Name is testlib", "[library]")
{
  auto const exported = testlib::exported_class {};
  REQUIRE(std::string("testlib") == exported.name());
}