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
    Vacancy(const int & , const string &, const vector<int> &);
    int getID() const ;
    vector<int> info() const;
    string getJob() const;
    ~Vacancy() = default;
private:
    int ID;
    string job;
    vector<int> requirements;
};




#endif //PROJECTC_VACANCY_HPP
