cmake_minimum_required(VERSION 3.5)
project(main LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
if (WIN32)
    set(CMAKE_EXE_LINKER_FLAGS ${CMAKE_EXE_LINKER_FLAGS} "-static")
endif ()

add_executable(matrix_mult matrix_mult.cpp)

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)
target_link_libraries(matrix_mult Threads::Threads)

if (CMAKE_CXX_COMPILER_ID MATCHES "Clang|AppleClang|GNU")
    target_compile_options(matrix_mult PRIVATE -Wall -Wextra -Wunreachable-code -Wpedantic)
endif ()
if (CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
    target_compile_options(matrix_mult PRIVATE /W4)
endif ()

if (CMAKE_CXX_COMPILER_ID MATCHES WIN32)
    set(CMAKE_EXE_LINKER_FLAGS ${CMAKE_EXE_LINKER_FLAGS} "-static")
endif ()


if (${CMAKE_VERSION} VERSION_GREATER 3.5)
    set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT main)
endif ()
