cmake_minimum_required(VERSION 3.14)
project(button_controller_test_harness CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/heads/main.zip
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_executable(button_controller_test_harness
    ${CMAKE_CURRENT_SOURCE_DIR}/button_controller_test_harness.cpp
)

target_compile_definitions(button_controller_test_harness PRIVATE
    UNIT_TEST
)

target_link_libraries(button_controller_test_harness PRIVATE
    GTest::gmock_main
)

target_include_directories(button_controller_test_harness PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}/../../button_controller"
)