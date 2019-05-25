//
// Created by mishok on 4/16/19.
//

#include "Candidate.hpp"

Candidate::Candidate():FIO(),email(),vacansies(0) {
}

bool Candidate::check(vector<int> skills, vector<int> requirements) {
    if (skills.size() == 0 && requirements.size()==0)
        return false;
    for (auto i : requirements)
        if ( std::find(skills.begin(), skills.end(),i) == skills.end())
            return false;
    return true;
}

Candidate::Candidate(User user, vector<Vacancy> vacancy) {
    for (auto i : vacancy){
        if (check(user.getSkills(),i.getRequirements())){
            this->FIO = user.getFIO();
            this->email = user.getEmail();
            this->vacansies.push_back(i.getID());
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

Candidate::~Candidate() {
}