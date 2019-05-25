//
// Created by mishok on 4/16/19.
//

#include "Vacancy.hpp"

Vacancy::Vacancy() : ID(0), job(), requirements() {
}

Vacancy::Vacancy(int id, string job_, vector<int> req) : ID(id), job(job_), requirements(req) {

}

int Vacancy::getID() {
    return this->ID;
}

string Vacancy::getJob() {
    return this->job;
}

vector<int> Vacancy::getRequirements()  {
    return this->requirements;
}

Vacancy::~Vacancy() {
}