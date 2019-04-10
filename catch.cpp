
#include "parser.h"
#define CATCH_CONFIG_MAIN


#include "catch.hpp"

TEST_CASE("Checking Parser functions", "[parser]") {
    SECTION("Functions Check") {
        parser check;
        REQUIRE(check.parse() == 0);
        REQUIRE(check.get_rez().flag == true);
    }
}
TEST_CASE("Checking Rezume functions", "[rezume]") {
    SECTION("Rrzume check") {
        rezume check;
        REQUIRE(!check.FName().empty());
        REQUIRE(!check.SName().empty());
        REQUIRE(!check.Phone().empty());
    }
}
