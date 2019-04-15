//
// Created by mishok on 4/16/19.
//

#include "User.hpp"

User::User() : FIO(), email(), skills(0) {
}

User::User(string fio, string Email, vector<int> skills_) : FIO(fio), email(Email), skills(skills_) {
}

string User::getEmail() {
    return this->email;
}

string User::getFIO() {
    return this->FIO;
}

vector<int> User::getSkills() const {
    return this->skills;
}


User::~User() {
}