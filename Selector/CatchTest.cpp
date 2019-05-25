#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "main.cpp"

TEST_CASE( "User class" , "[User]") {
    vector<int> A = {1,2,3};
    time_t date;
    User user("CEC","","+7985555223",date,"cec@ya.ru",A);
    REQUIRE(user.getEmail() == "cec@ya.ru");
    REQUIRE(user.getNumber() == "+7985555223");
    REQUIRE(user.getFIO() == "CEC");
    REQUIRE(user.info() == A);
}

TEST_CASE("Vacancy class", "[Vacancy]"){
    vector<int> A = {1,2,3};
    Vacancy vacancy(1,"CAC",A);
    REQUIRE(vacancy.getID() == 1);
    REQUIRE(vacancy.getJob() == "CAC");
    REQUIRE(vacancy.info() == A);
}


TEST_CASE("Candidate class" , "[Candidate]"){
    vector<int> A = {1,2,3};
    time_t date ;
    User user2("CEC","Panic","+7985555223",date,"cec@ya.ru",A);
    vector<int> B = {1,2};
    Vacancy vacancy2(1,"CAC",B);
    vector<Vacancy> vac;
    vac.push_back(vacancy2);
    vector<int> test = {1};
    Candidate candidate1 = Candidate::instance();
    REQUIRE(candidate1.getFIO() == "");
}

TEST_CASE("Pattern Memento" , "History"){
    vector<int> A = {1,2,3};
    time_t date;
    User user1("Maxim","","+7985555223",date,"cec@ya.ru",A);
    User user2("Pavel","","+7985555223",date,"cec@ya.ru",A);
    User user3("Emily","","+7985555223",date,"cec@ya.ru",A);
    User user4("dsasda","","+7985555223",date,"cec@ya.ru",A);
    User user5("Pweqqw","","+7985555223",date,"cec@ya.ru",A);

    vector<int> B = {1,2};
    vector<int> C = {4,5};
    Vacancy vacancy1(1,"CAC",B);
    Vacancy vacancy2(2,"LOL",C);
    vector<Vacancy> vac = {vacancy1,vacancy2};

    History history;

    Candidate candidate1 = Candidate::instance();
    candidate1.work(user1,vac);
    REQUIRE(candidate1.getFIO() == "Maxim");

    history.Push(candidate1.SaveCandidate());
    candidate1.work(user2,vac);
    REQUIRE(candidate1.getFIO() == "Pavel");

    candidate1.RestoreCandidate(history.Pop());
    REQUIRE(candidate1.getFIO() == "Maxim");

    history.Push(candidate1.SaveCandidate());
    candidate1.work(user3,vac);
    REQUIRE(candidate1.getFIO() == "Emily");

    history.Push(candidate1.SaveCandidate());
    candidate1.work(user4,vac);
    REQUIRE(candidate1.getFIO() == "dsasda");

    candidate1.RestoreCandidate(history.Pop());
    REQUIRE(candidate1.getFIO() == "Maxim");

    candidate1.RestoreCandidate(history.Pop());
    REQUIRE(candidate1.getFIO() == "Emily");
}