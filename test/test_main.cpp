#define CATCH_CONFIG_MAIN // This tells Catch to provide a main() - only do this in one cpp file
#include "../src/hc-06.hpp"
#include "catch.hpp"
#include "uart_test_bench.hpp"

// These test don't work yet

// TEST_CASE("HC06 name functions") {
//     UARTTestBench<ConstantRx> uart{0x59, 0x59, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10};
//     HC06 test(uart);
//     hwlib::string<50> newName = "Test naam";
//     test.setName(newName);
//     REQUIRE(newName == test.getName());
// }

// TEST_CASE("HC06 baud functions") {
//     UARTTestBench<ConstantRx> uart{0x59, 0x59, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10};
//     HC06 test(uart);
//     test.setBaud(HC06::BaudRates::EIGHT);
//     REQUIRE(115200 == test.getBaud());
// }