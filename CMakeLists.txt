cmake_minimum_required(VERSION 3.3)
project(Mmn18_20407)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c99")

set(SOURCE_FILES main.c rb_tree.c rb_tree.h)
add_executable(Mmn18_20407 ${SOURCE_FILES})