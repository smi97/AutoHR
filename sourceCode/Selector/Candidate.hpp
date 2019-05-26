//
// Created by mishok on 4/16/19.
//

#ifndef PROJECTC_CANDIDATE_HPP
#define PROJECTC_CANDIDATE_HPP
#include <thread>
#include <algorithm>
#include <queue>
#include "Vacancy.cpp"
#include "User.cpp"

class Candidate;
class Observer;

//void AddMailToDB(string mail){};

template <class T>
class Myqueue {
public:
    Myqueue() = default;
    void Push(const T & value){
        q.push(value);
    }
    T Pop(){
        if (!q.empty()) {
            T result = q.front();
            q.pop();
            return result;
        }
    }
    ~Myqueue() = default;
private:
    std::queue<T> q;
};

// Хранитель, который сохраняет состояние объекта Candidate
class CandidateMemento {
public:
    CandidateMemento(const string &fio, const string &email, const vector<int> &vacansies) : FIO(fio), Email(email), Vacansies(vacansies){}
    ~CandidateMemento() = default;
private:
    friend class Candidate;
    string FIO;
    string Email;
    vector<int> Vacansies;
};

class Candidate {
public:
    Candidate();
    Candidate(const User &, const vector<Vacancy> &);
    void printCandidate();
    string getFIO() const ;
    string getEmail() const ;
    vector<int> getVacansies() const ;
    CandidateMemento SaveCandidate ();
    void RestoreCandidate(CandidateMemento);
    ~Candidate() = default;
    void attach(Observer*);
    void notify();
private:
    vector<Observer*> obser;
    string FIO;
    string email;
    vector<int> vacansies;
    bool check(const vector<int> &, const vector<int> &);
};

// Выполняет только функцию хранения объекта CandidateMemento.
class History{
public:
    void Push(const CandidateMemento &);
    CandidateMemento Pop();
protected:
    Myqueue<CandidateMemento> history;
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

#endif //PROJECTC_CANDIDATE_HPP
