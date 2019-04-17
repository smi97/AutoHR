#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "main.cpp"

TEST_CASE( "User class" , "[User]") {
    vector<int> A = {1,2,3};
    User user("CEC","cec@ya.ru",A);
    REQUIRE(user.getEmail() == "cec@ya.ru");
    REQUIRE(user.getFIO() == "CEC");
    REQUIRE(user.getSkills() == A);
}

TEST_CASE("Vacancy class", "[Vacancy]"){
    vector<int> A = {1,2,3};
    Vacancy vacancy(1,"CAC",A);
    REQUIRE(vacancy.getID() == 1);
    REQUIRE(vacancy.getJob() == "CAC");
    REQUIRE(vacancy.getRequirements() == A);
}


TEST_CASE("Candidate class" , "[Candidate]"){
    vector<int> A = {1,2,3};
    User user2("CEC","cec@ya.ru",A);
    vector<int> B = {1,2};
    Vacancy vacancy2(1,"CAC",B);
    vector<Vacancy> vac;
    vac.push_back(vacancy2);
    vector<int> test = {1};
    Candidate candidate(user2,vac);
    REQUIRE(candidate.getFIO() == "CEC");
    REQUIRE(candidate.getVacansies() == test);
}