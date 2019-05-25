//
// Created by mishok on 4/16/19.
//

#ifndef PROJECTC_USER_HPP
#define PROJECTC_USER_HPP


#include <iostream>
#include <vector>
#include <ctime>
#include <chrono>

using std::vector;
using std::string;


class User {
public:
    User();
    void AddEmail(std::string mail);
    void AddFName(std::string Name);
    void AddSName(std::string Name);
    void AddNumber(std::string number);
    void AddSkill(size_t idx);
    bool operator[](const size_t &i);
    User(string, string, string, time_t , string, vector<int> );
    vector<int> info()const ;
    string getEmail();
    string getFIO();
    string getNumber();
    std::time_t* getDate();
    ~User() = default;
private:
    string FName;
    string SName;
    string Number;
    time_t Date;
    string Email;
    vector<int> Skills;
};


#endif //PROJECTC_USER_HPP
