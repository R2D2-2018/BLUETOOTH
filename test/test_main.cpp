#define CATCH_CONFIG_MAIN // This tells Catch to provide a main() - only do this in one cpp file
#include "catch.hpp"
#include "hc-05.hpp"
#include "hc-06.hpp"
#include "uart_lib.hpp"

TEST_CASE("Bluetooth baudrate HC-06", "[HC06]") {
    UARTLib::MockUART connection(9600, UARTLib::UARTController::ONE);
    Bluetooth::HC06 hc06(connection);
    hc06.setBaud(Bluetooth::HC06::BaudRates::NINE);
    REQUIRE(hc06.getBaud() == 230400);
}

TEST_CASE("Bluetooth baudrate HC-05", "[HC05]") {
    UARTLib::MockUART connection(9600, UARTLib::UARTController::ONE);
    hwlib::test::pin_out<> pin1, pin2;
    HC05 hc05(connection, pin1, pin2);
    hc05.setBaud(HC05::BaudRates::EIGHT);
    REQUIRE(hc05.getBaud() == "115200");
}

TEST_CASE("Bluetooth parity check mode HC-06", "[HC06]") {
    UARTLib::MockUART connection(9600, UARTLib::UARTController::ONE);
    Bluetooth::HC06 hc06(connection);
    hc06.setParityCheckMode(Bluetooth::HC06::ParityModes::EVEN);
    REQUIRE(hc06.getParityCheckMode() == Bluetooth::HC06::ParityModes::EVEN);
}

TEST_CASE("Bluetooth mode HC-05", "[HC05]") {
    UARTLib::MockUART connection(9600, UARTLib::UARTController::ONE);
    hwlib::test::pin_out<> pin1, pin2;
    HC05 hc05(connection, pin1, pin2);
    hc05.setMode(false);
    REQUIRE(hc05.getMode() == false);
}