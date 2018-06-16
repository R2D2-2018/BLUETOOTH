#define CATCH_CONFIG_MAIN // This tells Catch to provide a main() - only do this in one cpp file
#include "../src/hc-06.hpp"
#include "catch.hpp"

TEST_CASE("HC06 name functions") {
    HC06 test;
    hwlib::string<50> newName = "Test naam";
    test.setName(newName);
    REQUIRE(newName == test.getName());
}

TEST_CASE("HC06 baud functions") {
    HC06 test;
    unsigned int newBaud = 11520;
    test.setBaud(newBaud);
    REQUIRE(newBaud == test.getBaud());
}