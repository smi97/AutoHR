cmake_minimum_required(VERSION 3.13)
project(AutoHR)

set(CMAKE_CXX_STANDARD 14)

add_executable(AutoHR main.cpp DBController.cpp DBChecker.cpp)