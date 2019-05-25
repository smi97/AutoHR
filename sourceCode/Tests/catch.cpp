
#include "../Parser/parser.h"
#define CATCH_CONFIG_MAIN


#include "catch.hpp"

TEST_CASE("Checking Parser functions", "[parser]") {
    SECTION("Functions Check") {
        auto check = parser::instanse();
        REQUIRE(check.parse() == 0);
        REQUIRE(check.get_user().flag == true);
        REQUIRE(check.worker("text") == 0);
        user check2 = check.get_user();
        REQUIRE(!check2.FName().empty());
        REQUIRE(!check2.SName().empty());
        REQUIRE(!check2.Phone().empty());

    }
}

