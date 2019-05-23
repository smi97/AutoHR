cmake_minimum_required(VERSION 3.13)
project(ProjectC__)

set(CMAKE_CXX_STANDARD 17)
SET(CMAKE_CXX_FLAGS -pthread)
find_package(Boost COMPONENTS system filesystem REQUIRED)
IF (Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIR})

endif()
add_executable(ProjectC__ CatchTest.cpp)
