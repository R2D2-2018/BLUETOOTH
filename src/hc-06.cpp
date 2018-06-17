#include "hc-06.hpp"

HC06::HC06() : connection(9600, UARTController::ONE) {
}

bool HC06::testConnection() {
    const hwlib::string<2> message = "OK";

    // Set command
    connection << "AT";

    auto data = receive<2>();

    return compareString<2>(data, message);
}

void HC06::connect(int deviceID) {
    hwlib::cout << "Connect to device: " << deviceID << '\n';
}

void HC06::disconnect() {
    hwlib::cout << "Disconnect\n";
}

hwlib::string<50> HC06::getName() {
    return name;
}

bool HC06::setName(const hwlib::string<maxNameSize> &newName) {
    const hwlib::string<2> message = "OK";
    // Name + AT+NAME
    hwlib::string<maxNameSize + 7> command = "AT+NAME";
    command += newName;

    // Set command
    connection << command;

    // Get response
    auto data = receive<2>();
    bool wasSuccessful = compareString<2>(data, message);

    if (wasSuccessful) {
        name = newName;
    }

    return wasSuccessful;
}

void HC06::pair(int deviceID) {
    hwlib::cout << "Pair with device: " << deviceID << '\n';
}

uint8_t *HC06::search() {
    hwlib::cout << "Search for devices\n";
    return discoveredDevices;
}

void HC06::send(uint8_t *data) {
    hwlib::cout << "Sending data\n";
}

void HC06::setBaud(const unsigned int &baud) {
    currentBaudrate = baud;
    // uart-comm stuff to send new baud rate
    hwlib::cout << "Set baud rate to: " << baud << '\n';
}

unsigned int HC06::getBaud() {
    return currentBaudrate;
}

void HC06::setVisibility(bool visible) {
    hwlib::cout << "Set visibility\n";
}