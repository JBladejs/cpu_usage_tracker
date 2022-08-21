cmake_minimum_required(VERSION 3.22)
project(cpu_usage_tracker_tests C)

set(CMAKE_C_STANDARD 99)

configure_file(testfile testfile COPYONLY)

add_executable(cpu_usage_tracker_tests src/test.c)

target_link_libraries(cpu_usage_tracker_tests PRIVATE file_io)

add_test(cpu_usage_tracker cpu_usage_tracker_tests)