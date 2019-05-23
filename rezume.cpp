#include "rezume.h"

user::user() :  FirstName("noname"),
                SecondName("noname"),
                Date(boost::chrono::system_clock::to_time_t(boost::chrono::system_clock::now())),
                skills(SKILLS_COUNT, false),
                flag(false)  {}
void user::AddFName(std::string Name) {
     FirstName = Name;
}
void user::AddSName(std::string Name) {
     SecondName = Name;
}
void user::AddNumber(std::string number) {
    Number = number;
}
void user::AddSkill(size_t idx) {
    skills.push_back(idx);
}
void user::AddEmail(std::string mail) {
    Email = mail;
}
bool user::operator[](const size_t &i) { return skills[i]; }
std::string user::FName() { return  FirstName; }
std::string user::SName() { return  SecondName; }
std::string user::Phone() { return  Number; }
std::time_t* user::GiveDate() { return &Date; }
