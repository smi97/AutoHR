//
// Created by Maxim on 2019-04-08.
//
#include "DBController.cpp"
#define CATCH_CONFIG_MAIN

#include "catch.hpp"


TEST_CASE("Checking HRDB Functions", "[HRDataBaseController]" ) {

	SECTION( "Get Functions Check" ) {
		HRDataBaseController check;

		REQUIRE( check.getAllUsers() != nullptr );
		REQUIRE( check.getVacancies() != nullptr );
	}
	SECTION( "Add Functions Check" ) {
		HRDataBaseController check;
		Vacancy vc;
		User usr;
		REQUIRE( check.addVacancy(vc) == true );
		REQUIRE( check.addCriteriaToVacancy("", vc) == false );
		REQUIRE( check.addCriteriaToVacancy("fgcgvhb", vc) == true );
		REQUIRE( check.addUser(usr) == true );
	}
}


TEST_CASE("Checking DBController", "[DataBaseController]" ) {

	SECTION( "Get Functions Check" ) {
		DataBaseController check;
		std::string * str;

		REQUIRE( check.getRows("") != nullptr );

		REQUIRE( check.insertRows("", str) == false );
		REQUIRE( check.insertRows("fdgh", str) == true );

		REQUIRE( check.insertRows("", nullptr) == false );
		REQUIRE( check.insertRows("dfbgn", nullptr) == false );
		REQUIRE( check.insertRows("dfbgn", nullptr) == false );

		REQUIRE( check.insertColumn("", "") == false );
		REQUIRE( check.insertColumn("", "fdghfh") == false );
		REQUIRE( check.insertColumn("fdgfhf", "") == false );
		REQUIRE( check.insertColumn("fdghg", "dfhgfh") == true );

	}
}

TEST_CASE("Checking DataBase", "[DataBase]" ) {

	SECTION( "Get Functions Check" ) {
		DataBase check;
		std::string * str;

		REQUIRE( check.connect() == true );

		REQUIRE( check.buildQuery("", "") == "" );
		REQUIRE( check.runQuery() != "" );

		REQUIRE( check.disconnect() == true );


	}
}