#include <iostream>
#include <vector>
#include <chrono>
#include <ctime>

#define SKILLS_COUNT 2
#ifndef REZUME_H
#define REZUME_H


class rezume
{
private:
    std::string FirstName;
    std::string SecondName;
    std::string Number;
    std::time_t date;
    std::vector<bool> skills;
public:
    bool flag;
    rezume();
    void AddFName(std::string Name);
    void AddSName(std::string Name);
    void AddNumber(std::string number);
    void AddSkill(size_t idx);
    bool operator[](const size_t &i);
    std::string FName();
    std::string SName();
    std::string Phone();
    std::time_t* GiveDate();
};

#endif // REZUME_H
