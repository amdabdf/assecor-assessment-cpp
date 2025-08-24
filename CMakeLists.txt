cmake_minimum_required(VERSION 3.16)
project(customer_demo LANGUAGES CXX)

# Use C++17 without compiler-specific extensions
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Helper: add strong warnings per target (MSVC vs GCC/Clang)
function(set_target_warnings tgt)
  if (MSVC)
    target_compile_options(${tgt} PRIVATE /W4 /permissive-)
  else()
    target_compile_options(${tgt} PRIVATE -Wall -Wextra -Wpedantic)
  endif()
endfunction()

# ---- Library ----
# Static library with the archive implementation
add_library(customerlib STATIC
  src/customer_archive.cpp
)
# Expose the public headers to consumers of the library
target_include_directories(customerlib PUBLIC ${CMAKE_SOURCE_DIR}/include)
set_target_warnings(customerlib)

# ---- App ----
add_executable(app app/main.cpp)
target_link_libraries(app PRIVATE customerlib)
set_target_warnings(app)

# ---- Tests ----
# Enable ctest integration and the BUILD_TESTING option
include(CTest)
if (BUILD_TESTING)
  add_executable(unit_archive tests/unit_archive.cpp)
  target_link_libraries(unit_archive PRIVATE customerlib)
  set_target_warnings(unit_archive)
  add_test(NAME unit_archive COMMAND unit_archive)

  add_executable(unit_formatter tests/unit_formatter.cpp)
  target_link_libraries(unit_formatter PRIVATE customerlib)
  set_target_warnings(unit_formatter)
  add_test(NAME unit_formatter COMMAND unit_formatter)

  add_executable(integration tests/integration.cpp)
  target_link_libraries(integration PRIVATE customerlib)
  set_target_warnings(integration)
  add_test(NAME integration COMMAND integration)
endif()