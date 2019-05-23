
#include "parser.h"
#define CATCH_CONFIG_MAIN


#include "catch.hpp"

TEST_CASE("Checking Parser functions", "[parser]") {
    SECTION("Functions Check") {
        auto check = parser::instanse();
        REQUIRE(check.parse() == 0);
        REQUIRE(check.get_user().flag == true);
        REQUIRE(check.worker("text") == 0);

    }
}
TEST_CASE("Checking user functions", "[user]") {
    SECTION("User check") {
        user check;
        REQUIRE(!check.FName().empty());
        REQUIRE(!check.SName().empty());
        REQUIRE(check.Phone().empty());
        //REQUIRE((check.GiveDate()));
    }
}
