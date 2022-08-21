cmake_minimum_required(VERSION 3.22)
project(cpu_usage_tracker C)

set(CMAKE_C_STANDARD 99)

include(CTest)

file(GLOB FILE_IO_HEADER_FILES "src/file_io/*.h")
file(GLOB FILE_IO_SOURCE_FILES "src/file_io/*.c")

add_library(file_io ${FILE_IO_SOURCE_FILES} ${FILE_IO_HEADER_FILES})

file(GLOB HEADER_FILES "src/*.h" "src/threads/*.h")
file(GLOB SOURCE_FILES "src/*.c" "src/threads/*.c")

add_executable(cpu_usage_tracker ${SOURCE_FILES} ${HEADER_FILES})
target_link_libraries(cpu_usage_tracker PRIVATE file_io)

add_subdirectory(tests)
enable_testing()
