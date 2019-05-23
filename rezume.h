#include <iostream>
#include <vector>
#include <chrono>
#include <ctime>
#include <boost/chrono.hpp>
#include <boost/timer.hpp>
#include <boost/algorithm/string.hpp>


#define SKILLS_COUNT 2
#ifndef REZUME_H
#define REZUME_H


class user
{
private:
    std::string Email;
    std::string FirstName;
    std::string SecondName;
    std::string Number;
    std::time_t Date;
    std::vector<int> skills;
public:
    bool flag;
    user();
    void AddEmail(std::string mail);
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
