//
// Created by mishok on 4/16/19.
//

#include "Candidate.hpp"

Candidate::Candidate():FIO(),email(),vacansies() {
}

bool Candidate::check(const vector<int> & skills,const vector<int> & requirements) {
    if (skills.size() == 0 && requirements.size()==0){
        return false;
    }
    for (auto & i : requirements) {
        if (std::find(skills.begin(), skills.end(), i) == skills.end()){
            return false;
        }
    }
    return true;
}

Candidate::Candidate(const User & user, const vector<Vacancy> & vacancy) {
    for (auto & i : vacancy){
        if (check(user.info(), i.info())){
            this->FIO = user.getFIO();
            this->email = user.getEmail();
            this->vacansies.push_back(i.getID());
        }
    }
}

string Candidate::getFIO() const {
    return this->FIO;
}

string Candidate::getEmail() const {
    return this->email;
}

vector<int> Candidate::getVacansies() const {
    return this->vacansies;
}

void Candidate::printCandidate() {
    std::cout << this->FIO << " " << this->email << " ";
    for (auto i : this->vacansies) {
        std::cout << i << " ";
    }
    std::cout << std::endl;
}

CandidateMemento Candidate::SaveCandidate() {
    return  CandidateMemento(FIO, email, vacansies);
}

void Candidate::RestoreCandidate(CandidateMemento candidate_memento) {
    this->FIO = candidate_memento.FIO;
    this->email = candidate_memento.Email;
    this->vacansies = candidate_memento.Vacansies;
}

void History::Push( const CandidateMemento & candidate_memento) {
    history.Push(candidate_memento);
}

CandidateMemento History::Pop() {
    return history.Pop();
}

void Candidate::attach(Observer * obs) {
    obser.push_back(obs);
}

void Candidate::notify() {
    for (auto &i : obser)
        i->update();
}

Observer::Observer(Candidate *mod) {
    subject = mod;
    subject->attach(this);
}

Candidate* Observer::getSabject() {
    return subject;
}

JobObserver::JobObserver(Candidate * mod) : Observer(mod){}

void JobObserver::update() {
    string job = getSabject()->getEmail();
    //AddMailToBD(job);
}