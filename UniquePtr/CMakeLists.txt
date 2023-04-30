cmake_minimum_required(VERSION 3.0)

project(UniquePtr)

add_library(UniquePtr INTERFACE)

target_include_directories(UniquePtr INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
    $<INSTALL_INTERFACE:include>
)

install(TARGETS UniquePtr EXPORT UniquePtrTargets)

install(FILES UniquePtr.hpp DESTINATION include)

install(EXPORT UniquePtrTargets
    FILE UniquePtrTargets.cmake
    NAMESPACE UniquePtr::
    DESTINATION lib/cmake/UniquePtr
)

export(TARGETS UniquePtr FILE UniquePtrTargets.cmake)


include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/b796f7d44681514f58a683a3a71ff17c94edb0c1.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()
# find_package(GTest REQUIRED)

add_executable(
    UniquePtr_test
    test/UniquePtr_test.cpp
)
target_include_directories(
  UniquePtr_test PRIVATE
  ${CMAKE_CURRENT_SOURCE_DIR}/../../
)
target_link_libraries(
  UniquePtr_test
  GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(UniquePtr_test)

