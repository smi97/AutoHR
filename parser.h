#include <rezume.h>
#include <iostream>
#include <regex>
#include <fstream>
#include <ctime>
#include <chrono>
#include <string.h>
//static size_t SKILLS_COUNT = 2;
#ifndef PARSER_H
#define PARSER_H


class parser
{
private:
    rezume rez_;
    std::vector<std::string> criteria;
    std::string FileName;
public:
    parser();
    parser(const char* file_name, std::vector<std::string> &criterias);
    //~parser();
    int parse();
    void print_file(const char* file_name);
    void print();
    rezume get_rez();
};

#endif // PARSER_H
