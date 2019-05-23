//
// Created by mishok on 4/16/19.
//

#include "User.hpp"


User::User() : SName(), FName(), Number(), Date() , Email(), Skills(0) {
}

User::User(string first_name, string second_name, string  number, time_t date, string email, vector<int> skills) : FName(first_name), SName(second_name),
 Number(number), Date(date), Email(email), Skills(skills) {
}

string User::getEmail() {
    return this->Email;
}

string User::getFIO() {
    string FIO;
    if (!FName.empty())
        FIO = FName;
    if (!SName.empty())
        FIO += " " + SName;
    return FIO;
}

string User::getNumber() {
    if (!Number.empty())
        return Number;
    return "";
}

vector<int> User::info() const {
    return this->Skills;
}
void User::AddFName(string Name) {
    FName = Name;
}
void User::AddSName(string Name) {
    SName = Name;
}
void User::AddNumber(string number) {
    Number = number;
}
void User::AddSkill(size_t idx) {
    Skills.push_back(idx);
}
void User::AddEmail(string mail) {
    Email = mail;
}

User::~User() {
}
