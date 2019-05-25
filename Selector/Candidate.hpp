//
// Created by mishok on 4/16/19.
//

#ifndef PROJECTC_CANDIDATE_HPP
#define PROJECTC_CANDIDATE_HPP
#include "Vacancy.cpp"
#include "User.cpp"
#include <thread>
#include <algorithm>
#include <queue>

class Candidate;
class Observer;

void AddMailToBD(string mail){};
template <class T>
class Myqueu{
public:
    Myqueu() = default;
    void Push(T value){
        q.push(value);
    }
    T Pop(){
        if (!q.empty()) {
            T result = q.front();
            q.pop();
            return result;
        }
    }
    ~Myqueu() = default;
private:
    std::queue<T> q;
};


// Хранитель, который сохраняет состояние объекта Candidate
class Candidate_Memento{
public:
    Candidate_Memento(string fio, string email, vector<int> vacansies) : FIO(fio), Email(email), Vacansies(vacansies){}
    ~Candidate_Memento() = default;
private:
    friend class Candidate;
    string FIO;
    string Email;
    vector<int> Vacansies;class Candidate;
};

class Candidate {
public:
    friend void candidate(Candidate* , User , vector<Vacancy> );
    void printCandidate();
    string getFIO();
    string getEmail();
    vector<int> getVacansies();
    int work( User , vector<Vacancy>);
    Candidate_Memento SaveCandidate ();
    void RestoreCandidate(Candidate_Memento);
    static Candidate& instance();
    ~Candidate() = default;
    void attach(Observer*);
    void notify();
private:
    Candidate();
    vector<Observer*> obser;
    string FIO;
    string email;
    vector<int> vacansies;
    bool check(vector<int>, vector<int>);
};


// Выполняет только функцию хранения объекта CandidateMemento.
class History{
public:
    void Push(Candidate_Memento);
    Candidate_Memento Pop();
protected:
    Myqueu<Candidate_Memento> history;
};

// Паттерн наблюдатель
class Observer{
    Candidate * subject;
public:
    virtual void update() = 0;
    Observer( Candidate *);
protected:
    Candidate* getSabject();
    int getDivisor();
};


class JobObserver : public Observer{
public:
    JobObserver(Candidate*);
    void update() override;
};

void candidate(Candidate*, User , vector<Vacancy>);

#endif //PROJECTC_CANDIDATE_HPP
