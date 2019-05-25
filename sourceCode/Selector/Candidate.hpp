//
// Created by mishok on 4/16/19.
//

#ifndef PROJECTC_CANDIDATE_HPP
#define PROJECTC_CANDIDATE_HPP
#include "Vacancy.cpp"
#include "User.cpp"
#include <algorithm>

class Candidate {
public:
    Candidate();
    Candidate(User , vector<Vacancy> );
    void printCandidate();
    string getFIO();
    vector<int> getVacansies();
    ~Candidate();
private:
    string FIO;
    string email;
    vector<int> vacansies;
    bool check(vector<int>, vector<int>);
};


#endif //PROJECTC_CANDIDATE_HPP
