//
// Created by mishok on 4/16/19.
//

#ifndef PROJECTC_CANDIDATE_HPP
#define PROJECTC_CANDIDATE_HPP
#include "Vacancy.cpp"
#include "User.cpp"
#include <thread>
#include <algorithm>


class Candidate {
public:
    friend void candidate(Candidate* , User , vector<Vacancy> );
    void printCandidate();
    string getFIO();
    vector<int> getVacansies();
    int work( User , vector<Vacancy>);
    static Candidate& instance();
    ~Candidate();
private:
//    friend class Singleton<Candidate>;
    Candidate();
    string FIO;
    string email;
    vector<int> vacansies;
    bool check(vector<int>, vector<int>);
};

void candidate(Candidate*, User , vector<Vacancy>);

#endif //PROJECTC_CANDIDATE_HPP
