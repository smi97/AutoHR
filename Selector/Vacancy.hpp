//
// Created by mishok on 4/16/19.
//

#ifndef PROJECTC_VACANCY_HPP
#define PROJECTC_VACANCY_HPP


#include <iostream>
#include <vector>
#include <algorithm>

using std::vector;
using std::string;


class Vacancy {
public:
    Vacancy();
    Vacancy(int , string , vector<int> );
    Vacancy AddVacancy();
    int getID();
    vector<int> info();
    string getJob();
    ~Vacancy() = default;
private:
    int ID;
    string job;
    vector<int> requirements;
};


#endif //PROJECTC_VACANCY_HPP
