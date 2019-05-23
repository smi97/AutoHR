//
// Created by mishok on 4/16/19.
//

#include "Candidate.hpp"

Candidate::Candidate():FIO(),email(),vacansies(0) {
}

Candidate& Candidate::instance() {
    static Candidate instance;
    return instance;
}

bool Candidate::check(vector<int> skills, vector<int> requirements) {
    if (skills.size() == 0 && requirements.size()==0)
        return false;
    for (auto i : requirements)
        if ( std::find(skills.begin(), skills.end(),i) == skills.end())
            return false;
    return true;
}

void candidate(Candidate* p,User user, vector<Vacancy> vacancy) {
    for (auto i : vacancy){
        if (p->check(user.info(), i.info())){
            p->FIO = user.getFIO();
            p->email = user.getEmail();
            p->vacansies.push_back(i.getID());
        }
    }
}



string Candidate::getFIO() {
    return this->FIO;
}

vector<int> Candidate::getVacansies() {
    return this->vacansies;
}

void Candidate::printCandidate() {
    std::cout << this->FIO << " " << this->email << " ";
    for (auto i : this->vacansies)
        std::cout << i << " ";
    std::cout << std::endl;
}

int Candidate::work(User user, vector<Vacancy> vacancy){
    std::thread trd1(&candidate, this, user, vacancy );
    trd1.join();
}

Candidate::~Candidate() {
}