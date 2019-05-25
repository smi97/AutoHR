//
// Created by mishok on 4/16/19.
//

#ifndef PROJECTC_VACANCY_HPP
#define PROJECTC_VACANCY_HPP

#include <iostream>
#include <vector>

using std::vector;
using std::string;

class Vacancy {
public:
    Vacancy();
    Vacancy(int , string , vector<int> );
    int getID();
    vector<int> getRequirements();
    string getJob();
    ~Vacancy();
private:
    int ID;
    string job;
    vector<int> requirements;
};


#endif //PROJECTC_VACANCY_HPP
