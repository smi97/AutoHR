//
// Created by mishok on 4/16/19.
//

#include "User.hpp"


User::User() : SName(), FName(), Number(), Date() , Email(), Skills(0) {
}

User::User(const string & first_name, const string & second_name, const string & number, const time_t & date, const string & email, const vector<int> & skills) : FName(first_name), SName(second_name),
 Number(number), Date(date), Email(email), Skills(skills) {
}

string User::getEmail() const {
    return this->Email;
}

string User::getFIO() const {
    string FIO;
    if (!FName.empty()){
        FIO = FName;
    }
    if (!SName.empty()) {
        FIO += " " + SName;
    }
    return FIO;
}

string User::getNumber() const {
    if (!Number.empty())
        return Number;
    return "";
}

vector<int> User::info() const {
    return this->Skills;
}
void User::AddFName(const string & Name) {
    FName = Name;
}
void User::AddSName(const string & Name) {
    SName = Name;
}
void User::AddNumber(const string & number) {
    Number = number;
}
void User::AddSkill(const size_t & idx) {
    Skills.push_back(idx);
}
void User::AddEmail(const string & mail) {
    Email = mail;
}

