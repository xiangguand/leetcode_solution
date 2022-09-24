cmake_minimum_required(VERSION 3.16)

include(cmake/gcc-toolchain.cmake)

project(main)

# generate the leetcode executable file
add_subdirectory(leetcode)
