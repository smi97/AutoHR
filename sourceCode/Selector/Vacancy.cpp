//
// Created by mishok on 4/16/19.
//

#include "Vacancy.hpp"


vector<string> GETSKILLS(){
    vector<string> skills;
    return skills;
}

void AddSkillsToBD (vector<string> skills){
}

Vacancy::Vacancy() : ID(), job(), requirements() {
}

Vacancy::Vacancy(const int & id, const string & job_, const vector<int> & req) : ID(id), job(job_), requirements(req) {
}

int Vacancy::getID() const {
    return this->ID;
}

string Vacancy::getJob() const {
    return this->job;
}

vector<int> Vacancy::info() const {
    return this->requirements;
}