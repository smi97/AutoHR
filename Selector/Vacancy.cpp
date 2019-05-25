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

vector<int> Vacancy::info()  {
    return this->requirements;
}

Vacancy Vacancy::AddVacancy() {
    vector<string> skills = GETSKILLS();
    std::cout << "Job : " ;
    std::cin >> job;
    string command;
    std::cin >> command;
    vector<string> new_skills;
    while (command == "+"){
        std::cout << "Введите требование: ";
        string skill;
        std::cin >> skill;
        vector<string>::iterator it = std::find(skills.begin(), skills.end(),skill);
        if (it != skills.end()){
            requirements.push_back(it-skills.begin());
        }
        else{
            new_skills.push_back(skill);
            requirements.push_back(new_skills.size() + skills.size());
        }
        std::cin >> command;
    }
    if (!new_skills.empty())
        AddSkillsToBD(new_skills);
}