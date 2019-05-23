#include "parser.h"

//функция для парсинга в потоке
void parsing(std::ifstream &stream, std::vector<std::string> criterias, parser *p) {
    if (!stream.is_open())
        return;
    user usr;
    boost::regex reg_n(".*(N|n)ame.? (.*)\\.");
    std::string buf;
    boost::regex reg_number("\\x2B{0,1}[0-9]\\x28{0,1}[0-9]{3}\\x29{0,1}[0-9]{3}\\x2D{0,1}[0-9]{2}\\x2D{0,1}[0-9]{2}");
    if (stream.is_open()) {
           while (getline(stream, buf)) {
               boost::smatch match;
               for (size_t i = 0; i < criterias.size(); i++) {
                   boost::regex reg(criterias[i]);
                   if (boost::regex_search(buf, match, reg)) {
                       usr.AddSkill(i);
                       criterias[i] = match[0];
                   }
               }
               if (boost::regex_search(buf, match, reg_number)) usr.AddNumber(match[0]);
               if (boost::regex_search(buf, match, reg_n)) {
                   if (!usr.flag) {
                       usr.AddFName(match[2]);
                       usr.flag = true;
                   }
                   else usr.AddSName(match[2]);
               }
           }
       }
    p->Users.push(usr);
    stream.close();
    p->notify();
}

void AddUserToBD(user usr) {
    //std::cout << "usr.FName()" << std::endl;
}

parser::parser()
{
    criteria = { "c++", "python"};
    FileName = "text";
}

parser& parser::instanse(){
    static parser object;
    return object;
}

//запуск потока
int parser::worker(const char *file_name) {
    std::ifstream stream(file_name);
    if (!stream.is_open())
        return 1;
    std::thread thr(parsing, std::ref(stream), criteria, this);
    thr.join();
    return 0;
}


int parser::parse() {
    std::ifstream stream(FileName);
    if (!stream.is_open())
        return 1;
    boost::regex reg_n(".*(N|n)ame.? (.*)\\.");
    std::string buf;
    boost::regex reg_number("\\x2B{0,1}[0-9]\\x28{0,1}[0-9]{3}\\x29{0,1}[0-9]{3}\\x2D{0,1}[0-9]{2}\\x2D{0,1}[0-9]{2}");
    if (stream.is_open()) {
           while (getline(stream, buf)) {
               boost::smatch match;
               for (size_t i = 0; i < criteria.size(); i++) {
                   boost::regex reg(criteria[i]);
                   if (boost::regex_search(buf, match, reg)) {
                       User.AddSkill(i);
                       criteria[i] = match[0];
                   }
               }
               if (boost::regex_search(buf, match, reg_number)) User.AddNumber(match[0]);
               if (boost::regex_search(buf, match, reg_n)) {
                   if (!User.flag) {
                       User.AddFName(match[2]);
                       User.flag = true;
                   }
                   else User.AddSName(match[2]);
               }
           }
       }
    stream.close();
    return 0;
}

void parser::attach(Observer *_obs) {
    obs.push_back(_obs);
}

void parser::notify()  {
    for (auto &iter : obs)
        iter->update();
}

user parser::get_user() {
    return Users.top();
}

void parser::updateSkills(std::vector<std::string> criterias) {
    criteria = criterias;
}

void parser::setCurrent(State *s) {
    current = s;
}

void parser::on(){}

void parser::off(){}


Observer::Observer(parser *mod) {
    subject = mod;
    subject->attach(this);
}

parser* Observer::getSubject() {
    return subject;
}

ParseObserver::ParseObserver(parser *mod) : Observer(mod){}

void ParseObserver::update() {
    AddUserToBD((getSubject()->get_user()));
}

void OFF::on(parser *m){
    m->setCurrent(new ON());
    delete this;
}

void ON::off(parser *m)
{
  m->setCurrent(new OFF());
  delete this;
}

