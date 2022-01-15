cmake_minimum_required(VERSION 3.21)
project(say)

set(CMAKE_CXX_STANDARD 17)

add_executable(yoga main.cpp model.h play.cpp play.h model.cpp)
