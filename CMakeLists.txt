project(libfuture-c++)

cmake_minimum_required (VERSION 2.6)
if (NOT CMAKE_VERSION VERSION_LESS 2.8.4)
    cmake_policy (SET CMP0017 NEW)
endif()

include(CMakeParseArguments)

set(CMAKE_ALLOW_LOOSE_LOOP_CONSTRUCTS TRUE)
message(STATUS "Project source dir = ${PROJECT_SOURCE_DIR}")
message(STATUS "Project build dir = ${CMAKE_BINARY_DIR}")

include_directories(include)

add_executable(function_bind
               examples/function_bind.cc
               include/future/bind.h
               include/future/function.h
               include/future/internal.h
               include/future/placeholders.h)
