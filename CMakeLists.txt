cmake_minimum_required(VERSION 3.2)
project(paoo_tema3)
add_executable(paoo_tema3 main.cpp)
set(CMAKE_CXX_FLAGS "-pthread")
find_package(Threads)

