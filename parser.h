#include <rezume.h>
#include <iostream>
#include <regex>
#include <fstream>
#include <ctime>
#include <chrono>
#include <string.h>
#include <boost/regex.hpp>
#include <thread>
#include <boost/thread.hpp>
#include <stack>
//static size_t SKILLS_COUNT = 2;


class Observer;
class parser;
class State;

void AddUserToBD(user usr);

class parser
{
private:
    user User;
    std::stack<user> Users;
    std::vector<std::string> criteria;
    std::vector<Observer*> obs;
    State *current;
    std::string FileName;
    parser();
public:
    static parser& instanse();
    ~parser() = default;
    void attach(Observer *_obs);
    friend void parsing(std::ifstream &stream, std::vector<std::string> criterias, parser *p);
    int parse();
    int worker(const char* file_name);
    void updateSkills(std::vector<std::string> criterias);
    user get_user();
    void notify();
    void on();
    void off();
    void setCurrent(State *s);

};

void parsing(std::ifstream &stream, std::vector<std::string> criterias, parser *p);

class Observer
{
    parser *subject;
public:
    virtual void update() = 0;
protected:
    parser *getSubject();
    int getDivisor();
    Observer(parser *mod);
    virtual ~Observer() = default;
};

class ParseObserver: public Observer {
  public:
    ParseObserver(parser *mod);
    void update() override;
};

class State
{
  public:
    virtual void on(parser *m){}
    virtual void off(parser *m){}
};



class ON: public State
{
  public:
    ON(){}
    ~ON(){}
    void off(parser *m);
};

class OFF: public State
{
  public:
    OFF(){}
    ~OFF(){}
    void on(parser *m);
};

