cmake_minimum_required(VERSION 3.22)
project(cpu_usage_tracker C)

set(CMAKE_C_STANDARD 99)

if (CMAKE_C_COMPILER_ID STREQUAL "Clang")
    message("Using Clang Compiler")
#    add_compile_options(-Weverything)
elseif(CMAKE_C_COMPILER_ID STREQUAL "GNU")
    message("Using GNU Compiler")
#    add_compile_options(-Wall -Wextra)
endif()

include(CTest)

file(GLOB FILE_IO_HEADER_FILES "src/file_io/*.h")
file(GLOB FILE_IO_SOURCE_FILES "src/file_io/*.c")

file(GLOB HELPER_HEADER_FILES "src/helper/*.h")
file(GLOB HELPER_SOURCE_FILES "src/helper/*.c")

file(GLOB COLLECTIONS_HEADER_FILES "src/collections/*.h")
file(GLOB COLLECTIONS_SOURCE_FILES "src/collections/*.c")

file(GLOB HEADER_FILES "src/*.h" "src/threads/*.h")
file(GLOB SOURCE_FILES "src/*.c" "src/threads/*.c")

add_library(file_io ${FILE_IO_SOURCE_FILES} ${FILE_IO_HEADER_FILES})
add_library(helper ${HELPER_SOURCE_FILES} ${HELPER_HEADER_FILES})
add_library(collections ${COLLECTIONS_SOURCE_FILES} ${COLLECTIONS_HEADER_FILES})

add_executable(cpu_usage_tracker ${SOURCE_FILES} ${HEADER_FILES})
target_link_libraries(cpu_usage_tracker PRIVATE file_io helper collections)

add_subdirectory(tests)
enable_testing()
