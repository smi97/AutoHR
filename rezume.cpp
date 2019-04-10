#include "rezume.h"

rezume::rezume() : FirstName("noname"), SecondName("noname"), date(std::chrono::system_clock::to_time_t(std::chrono::system_clock::now())), skills(SKILLS_COUNT, false), flag(false)  {}
void rezume::AddFName(std::string Name) {
     FirstName = Name;
}
void rezume::AddSName(std::string Name) {
     SecondName = Name;
}
void rezume::AddNumber(std::string number) {
    Number = number;
}
void rezume::AddSkill(size_t idx) {
    skills[idx] = true;
}
bool rezume::operator[](const size_t &i) { return skills[i]; }
std::string rezume::FName() { return  FirstName; }
std::string rezume::SName() { return  SecondName; }
std::string rezume::Phone() { return  Number; }
std::time_t* rezume::GiveDate() { return &date; }
