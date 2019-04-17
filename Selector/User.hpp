//
// Created by mishok on 4/16/19.
//

#ifndef PROJECTC_USER_HPP
#define PROJECTC_USER_HPP

#include <iostream>
#include <vector>

using std::vector;
using std::string;


class User {
public:
    User();
    User(string , string , vector<int> );
    vector<int> getSkills()const ;
    string getEmail();
    string getFIO();
    ~User();
private:
    string FIO;
    string email;
    vector<int> skills;
};


#endif //PROJECTC_USER_HPP
