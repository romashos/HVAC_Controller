cmake_minimum_required(VERSION 3.10)
project(buzzer_controller_test_harness CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(buzzer_controller_test_harness
    buzzer_controller_test_harness.cpp
)

target_include_directories(buzzer_controller_test_harness PRIVATE
    ${CMAKE_SOURCE_DIR}/../../buzzer_controller
)