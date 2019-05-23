//
// Created by mishok on 5/23/19.
//

#ifndef PROJECTC_FACTORY_HPP
#define PROJECTC_FACTORY_HPP

#include <vector>
#include <cassert>
#include "Vacancy.hpp"
#include "User.hpp"

//using std::vector;
//
//
//enum Skill_ID { JOB=0, USER};
//
//// Иерархия классов игровых персонажей
//class Skill
//{
//public:
//    virtual  vector<int> info() = 0;
//    virtual ~Skill() {}
//    // Параметризированный статический фабричный метод
//    static Skill* createSkill();
//};
//
//class Factory
//{
//public:
//    virtual Skill* createSkill() = 0;
//    virtual ~Factory() {}
//};
//
//class VacancyFactory: public Factory
//{
//public:
//    Skill* createSkill() {
//        return new Vacancy;
//    }
//};
//
//class UserFactory: public Factory
//{
//public:
//    Skill* createSkill() {
//        return new User;
//    }
//};

#endif //PROJECTC_FACTORY_HPP
