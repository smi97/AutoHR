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
    void AddEmail(const string & mail);
    void AddFName(const string & Name);
    void AddSName(const string & Name);
    void AddNumber(const string & number);
    void AddSkill(const size_t & idx);
    bool operator[](const size_t &i);
    User(const string &, const string &, const string &, const time_t &, const string &, const vector<int> & );
    vector<int> info()const ;
    string getEmail() const;
    string getFIO() const;
    string getNumber() const;
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
