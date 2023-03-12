#pragma once

#include <string>
#include <testlib/export.hpp>

namespace testlib
{
  /**
   * @brief Reports the name of the library
   */
  class TESTLIB_EXPORT exported_class
  {
  public:
    /**
     * @brief Initializes the name field to the name of the project
     */
    exported_class();

    /**
     * @brief Returns a non-owning pointer to the string stored in this class
     */
    auto name() const -> const char*;

  private:
    std::string m_name;
  };
}
