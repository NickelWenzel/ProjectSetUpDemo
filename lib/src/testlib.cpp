#include <testlib/testlib.hpp>

#include <fmt/core.h>

testlib::exported_class::exported_class()
    : m_name {fmt::format("{}", "testlib")}
{
}

auto testlib::exported_class::name() const -> const char*
{
  return m_name.c_str();
}
