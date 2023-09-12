cmake_minimum_required(VERSION 3.25)
project(cminipackTest)

set(CMAKE_CXX_STANDARD 17)

add_executable(cminipackTest main.cpp cminpack.h cminpack.cpp cminpack.cpp)
