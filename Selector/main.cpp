#include <iostream>
#include <vector>
#include <algorithm>

using std::vector;
using std::string;

void getUser();

void getVacancy();

void email_to_send();

class Vacancy {
public:
    Vacancy();
    Vacancy(int &, string &, vector<int> &);
    int getID();
    vector<int> getRequirements() const;
    string getJob();
    ~Vacancy();
private:
    int ID;
    string job;
    vector<int> requirements;
};

Vacancy::Vacancy() : ID(0), job(), requirements() {
}

Vacancy::Vacancy(int &id, string &job_, vector<int> &req) : ID(id), job(job_), requirements(req) {

}

int Vacancy::getID() {
    return this->ID;
}

string Vacancy::getJob() {
    return this->job;
}

vector<int> Vacancy::getRequirements() const {
    return this->requirements;
}

Vacancy::~Vacancy() {
}

class User {
public:
    User();
    User(string &, string &, vector<int> &);
    vector<int> getSkills()const ;
    string getEmail();
    string getFIO();
    ~User();
private:
    string FIO;
    string email;
    vector<int> skills;
};

User::User() : FIO(), email(), skills(0) {
}

User::User(string &fio, string &Email, vector<int> &skills_) : FIO(fio), email(Email), skills(skills_) {
}

string User::getEmail() {
    return this->email;
}

string User::getFIO() {
    return this->FIO;
}

vector<int> User::getSkills() const {
    return this->skills;
}


User::~User() {
}


class Candidate {
public:
    Candidate();
    Candidate(User &, vector<Vacancy> &);
    bool check(const vector<int>&, const vector<int>&);
    void printCandidate();
    ~Candidate();
private:
    string FIO;
    string email;
    vector<int> vacansies;
};

Candidate::Candidate():FIO(),email(),vacansies(0) {
}

bool Candidate::check(const vector<int> &skills, const vector<int> &requirements) {
    if (skills.size() == 0 && requirements.size()==0)
        return false;
    for (auto i : requirements)
        if ( std::find(skills.begin(), skills.end(),i) == skills.end())
            return false;
    return true;
}

Candidate::Candidate(User &user, vector<Vacancy> &vacancy) {
    for (auto i : vacancy){
        if (check(user.getSkills(),i.getRequirements())){
            this->FIO = user.getFIO();
            this->email = user.getEmail();
            this->vacansies.push_back(i.getID());
        }
    }
}

void Candidate::printCandidate() {
    std::cout << this->FIO << " " << this->email << " ";
    for (auto i : this->vacansies)
        std::cout << i << " ";
    std::cout << std::endl;
}

Candidate::~Candidate() {
}

