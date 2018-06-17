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

hwlib::string<HC06::maxNameSize> HC06::getName() {
    return name;
}

bool HC06::setName(const hwlib::string<maxNameSize> &newName) {
    // Send command to UC06
    bool wasSuccessful = sendCommand<maxNameSize>(CommandTypes::name, newName);

    // Change name if it was successful
    if (wasSuccessful) {
        name = newName;
    }

    return wasSuccessful;
}

hwlib::string<HC06::pinSize> HC06::getPincode() {
    return pincode;
}

bool HC06::setPincode(hwlib::string<pinSize> newPincode) {
    // Send command to UC06
    bool wasSuccessful = sendCommand<maxNameSize>(CommandTypes::pin, newPincode);

    // Change name if it was successful
    if (wasSuccessful) {
        pincode = newPincode;
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

uint32_t HC06::getBaud() {
    return BaudRateValues[static_cast<uint32_t>(baudrate)];
}

bool HC06::setBaud(BaudRates baud) {
    // Send command to UC06
    bool wasSuccessful = sendCommand<maxNameSize>(CommandTypes::baud, BaudRateStrings[static_cast<int>(baud)]);

    // Change name if it was successful
    if (wasSuccessful) {
        baudrate = baud;
    }

    return wasSuccessful;
}

void HC06::setVisibility(bool visible) {
    hwlib::cout << "Set visibility\n";
}