#define CATCH_CONFIG_MAIN // This tells Catch to provide a main() - only do this in one cpp file
#include "catch.hpp"
#include "hc-05.hpp"
#include "hc-06.hpp"

TEST_CASE("Bluetooth baudrate HC-06", "[HC06]") {
    UARTLib::HardwareUART connection(9600, UARTLib::UARTController::ONE);
    Bluetooth::HC06 hc06(connection);
    hc06.setBaud(Bluetooth::HC06::BaudRates::NINE);
    REQUIRE(hc06.getBaud == 230400);
}

TEST_CASE("Bluetooth baudrate HC-05", "[HC05]") {
    UARTLib::HardwareUART connection(9600, UARTLib::UARTController::ONE);
    HC05 hc05(connection);`
    hc05.setBaud(Bluetooth::HC06::BaudRates::EIGHT);
    REQUIRE(hc05.getBaud == 115200);
}

TEST_CASE("Bluetooth name HC-06", "[HC06]") {
    UARTLib::HardwareUART connection(9600, UARTLib::UARTController::ONE);
    Bluetooth::HC06 hc06(connection);
    hc06.setName("NewName");
    REQUIRE(hc06.getName() == "NewName");
}

TEST_CASE("Bluetooth name HC-05", "[HC05]") {
    UARTLib::HardwareUART connection(9600, UARTLib::UARTController::ONE);
    HC05 hc05(connection);
    hc05.setName("ANewName");
    REQUIRE(hc05.getName() == "ANewName");
}

TEST_CASE("Bluetooth pincode HC-06", "[HC06]") {
    UARTLib::HardwareUART connection(9600, UARTLib::UARTController::ONE);
    Bluetooth::HC06 hc06(connection);
    hc06.setPincode("9165");
    REQUIRE(hc06.getPincode() == "9165");
}

TEST_CASE("Bluetooth pincode HC-05", "[HC05]") {
    UARTLib::HardwareUART connection(9600, UARTLib::UARTController::ONE);
    HC05 hc05(connection);
    hc05.setPincode("6543");
    REQUIRE(hc05.getPincode() == "6543");
}

TEST_CASE("Bluetooth parity check mode HC-06", "[HC06]") {
    UARTLib::HardwareUART connection(9600, UARTLib::UARTController::ONE);
    Bluetooth::HC06 hc06(connection);
    hc06.setParityCheckMode(Bluetooth::HC06::ParityModes::EVEN);
    REQUIRE(hc06.getParityCheckMode() == Bluetooth::HC06::ParityModes::EVEN);
}

TEST_CASE("Bluetooth parity check mode HC-05", "[HC05]") {
    UARTLib::HardwareUART connection(9600, UARTLib::UARTController::ONE);
    HC05 hc05(connection);
    hc05.setParityCheckMode(ParityModes::ODD);
    REQUIRE(hc05.getParityCheckMode == ParityModes::ODD);
}