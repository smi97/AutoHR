cmake_minimum_required(VERSION 3.9)
project(AutoHR)

set(CMAKE_CXX_STANDARD 17)

add_executable(AutoHR main.cpp
        sourceCode/DataBase/DataBaseConnection.cpp
        sourceCode/DataBase/DataBase.cpp
        sourceCode/DataBase/DataBaseController.cpp
        sourceCode/DataBase/HRDataBaseController.cpp
        sourceCode/Mail/Mail_Recv.cpp
        sourceCode/Mail/Mail_Send.cpp
        sourceCode/Parser/parser.cpp
        sourceCode/Selector/Candidate.cpp
        sourceCode/Selector/User.cpp
        sourceCode/Selector/Vacancy.cpp

        )

include_directories("/usr/local/include/")
target_link_libraries(AutoHR "/usr/lib/libpq.dylib")
add_library(libpqxx SHARED IMPORTED)



find_package( Boost REQUIRED COMPONENTS program_options regex )
include_directories( ${Boost_INCLUDE_DIRS} )

target_link_libraries( AutoHR ${Boost_PROGRAM_OPTIONS_LIBRARY} ${Boost_REGEX_LIBRARY} )
