/*#include <iostream>
#include <regex>
#include <fstream>
#include <ctime>
#include <chrono>
#include <string.h>
#include <parser.h>*/

#include "parser.cpp"
#include "catch.hpp"

#define CATCH_CONFIG_MAIN
CATCH_CONFIG_MAIN
/*int main(int argc, char *argv[])
{
    std::vector<std::string> criteria;
    criteria.push_back("python");
    criteria.push_back("\\x43\\x2B\\x2B");
    parser parse(argv[1], criteria);
    parse.parse();
    parse.print_file(argv[2]);
    parse.print();
    return 0;
}*/
