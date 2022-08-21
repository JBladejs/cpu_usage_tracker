cmake_minimum_required(VERSION 3.22)
project(cpu_usage_tracker C)

set(CMAKE_C_STANDARD 99)

file(GLOB HEADER_FILES "src/*.h" "src/*/*.h")
file(GLOB SOURCE_FILES "src/*.c" "src/*/*.c")

add_executable(cpu_usage_tracker ${SOURCE_FILES} ${HEADER_FILES})
