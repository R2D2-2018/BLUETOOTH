#include "hc-06.hpp"

HC06::HC06() : connection(9600, UARTController::ONE) {
}

bool HC06::testConnection() {

    std::array<char, 2> data;
    const std::array<char, 2> message = {'O', 'K'};

    // Set command
    connection << "AT";

    // Wait for response, timeout at 10 us
    auto start = hwlib::now_us();
    while (connection.available() < 2 || hwlib::now_us() - start < 10) {
        // hwlib::cout << connection.available();
    }
    for (unsigned int i = 0; i <= connection.available(); i++) {
        data[i] = connection.receive();
    }

    for (int i = 0; i < 2; ++i) {
        if (data[i] != message[i]) {
            return false;
        }
    }

    return true;
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

int HC06::getStatus() {
    hwlib::cout << "Get status\n";
    return 0;
}

void HC06::pair(int deviceID) {
    hwlib::cout << "Pair with device: " << deviceID << '\n';
}

void HC06::receive(uint8_t *data) {
    hwlib::cout << "Receive data\n";
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

void HC06::setName(const hwlib::string<50> &newName) {
    name = newName;
    // uart-comm stuff to send new name (max 20 chars)
}

void HC06::setVisibility(bool visible) {
    hwlib::cout << "Set visibility\n";
}