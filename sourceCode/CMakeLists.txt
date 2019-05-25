cmake_minimum_required(VERSION 3.13)
project(AutoHR)

set(CMAKE_CXX_STANDARD 17)

add_executable(AutoHR main.cpp DataBaseConnection.cpp DataBase.cpp DataBaseController.cpp HRDataBaseController.cpp User.cpp Vacancy.cpp)

include_directories("/usr/local/include/")
target_link_libraries(AutoHR "/usr/lib/libpq.dylib")
add_library(libpqxx SHARED IMPORTED)

