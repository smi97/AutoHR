// CatchTest_Mail_Class.cpp
#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "Mail_Class.cpp"

TEST_CASE( "Mail class checker", "[Mail.save_file]" ) {
    Mail mail;
    REQUIRE( mail.save_file("", 12) == false );
    REQUIRE( mail.save_file("resumes", 1) == true );
    REQUIRE( mail.save_file("Project/HR", 444) == true );
    REQUIRE( mail.save_file("", 0) == false );
    REQUIRE( mail.save_file("file", -57) == false );
    REQUIRE( mail.save_file("file", 0) == false );
}

TEST_CASE( "Mail class checker", "[Mail.connect]" ) {
    Mail mail;
    REQUIRE( mail.connect("login", "") == false );
    REQUIRE( mail.connect("login@gmail.com", "qwerty") == true );
    REQUIRE( mail.connect("ProjectHR@yandex.ru", "super") == true );
    REQUIRE( mail.connect("", "") == false );
    REQUIRE( mail.connect("pavel@mail.ru", "") == false );
    REQUIRE( mail.connect("", "password") == false );
    REQUIRE( mail.connect("///", "true") == false );
}