// CatchTest_Mail_Class.cpp
#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "Mail_Class.cpp"

TEST_CASE( "Mail class checker", "[Mail.save_file]" ) {
    Mail mail;
    REQUIRE( mail.save_file("", 12) == false );
    REQUIRE( mail.save_file("resumes", 1) == true );
    REQUIRE( mail.save_file("Project/HR", 444) == true );
    REQUIRE( mail.save_file("", 12) == false );
}