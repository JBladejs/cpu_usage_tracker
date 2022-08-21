cmake_minimum_required(VERSION 3.22)
project(cpu_usage_tracker_tests C)

set(CMAKE_C_STANDARD 99)

configure_file(test_proc_stat test_proc_stat COPYONLY)

add_executable(file_io_tests src/file_io_tester.c)

target_link_libraries(file_io_tests PRIVATE file_io)
target_link_libraries(file_io_tests PRIVATE file_io)
target_link_libraries(file_io_tests PRIVATE file_io)

add_test(file_io_tests file_io_tests)