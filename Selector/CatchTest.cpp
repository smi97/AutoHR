#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "main.cpp"

TEST_CASE( "Candidate class checker" , "[Candidate.check]") {
    Candidate candidate;
    REQUIRE(candidate.check({},{}) == false);
    REQUIRE(candidate.check({1, 2, 3}, {1, 2}) == true);
    REQUIRE(candidate.check({1, 2, 3}, {1, 2,4}) == false);
    REQUIRE(candidate.check({1},{}) == true);
}

