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

TEST_CASE( "MailSend class checker", "[MailSend.send]" ) {
    MailSend mail;
    REQUIRE( mail.send("login", "", 0) == false );
    REQUIRE( mail.send("login@gmail.com", "qwerty", 11222) == true );
    REQUIRE( mail.send("login@gmail.com", "qwerty", 0) == false );
    REQUIRE( mail.send("ProjectHR@yandex.ru", "super", 444) == true );
    REQUIRE( mail.send("", "", ) == false );
    REQUIRE( mail.send("pavel@mail.ru", "", 940) == false );
    REQUIRE( mail.send("", "password", -666) == false );
    REQUIRE( mail.send("///", "true", 4) == false );
}

TEST_CASE( "MailSend class checker", "[MailSend.connect_to_smtp]" ) {
    MailSend mail;
    REQUIRE( mail.connect_to_smtp("login", "", 0) == false );
    REQUIRE( mail.connect_to_smtp("login@gmail.com", "qwerty", 11222) == true );
    REQUIRE( mail.connect_to_smtp("login@gmail.com", "qwerty", 0) == false );
    REQUIRE( mail.connect_to_smtp("ProjectHR@yandex.ru", "super", 444) == true );
    REQUIRE( mail.connect_to_smtp("", "", ) == false );
    REQUIRE( mail.connect_to_smtp("pavel@mail.ru", "", 940) == false );
    REQUIRE( mail.connect_to_smtp("", "password", -666) == false );
    REQUIRE( mail.connect_to_smtp("///", "true", 4) == false );
}

int main() {
    return 0;
}