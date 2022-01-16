cmake_minimum_required(VERSION 3.21)
project(yoga)

set(CMAKE_CXX_STANDARD 17)

add_executable(yoga main.cpp play.cpp play.h)

add_executable(stringify main_stringify.cpp main_stringify.cpp)