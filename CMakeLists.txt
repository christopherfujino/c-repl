# Ubuntu 25.10
cmake_minimum_required(VERSION 3.31)

project(my_great_project VERSION 0.1)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_compile_options(-Wall -Werror -Wpedantic -Wextra)

add_executable(main main.cc)

# TODO make this portable
target_link_libraries(main
  ${CMAKE_CURRENT_SOURCE_DIR}/ignore/libffi/aarch64-unknown-linux-gnu/.libs/libffi.a)
target_include_directories(main BEFORE PRIVATE
  ${CMAKE_CURRENT_SOURCE_DIR}/ignore/libffi/aarch64-unknown-linux-gnu/include)

#target_link_libraries(main PRIVATE lib)
#
#add_library(lib lib.cpp)
