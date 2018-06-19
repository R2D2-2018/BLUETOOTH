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
    // Get the length of the expected response message
    // We cannot use the responses array because hwlib::string has no constexpr constructor (yet) and therefore cannot make the
    // array constexpr, if we could we could use:
    // static constexpr const auto &length = responses[static_cast<int>(CommandTypes::name)].length();
    static constexpr const auto length = 9; // "OKsetname" length
    // Send command to UC06
    bool wasSuccessful = sendCommand<maxNameSize, length>(CommandTypes::name, newName);

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
    // Get the length of the expected response message
    // We cannot use the responses array because hwlib::string has no constexpr constructor (yet) and therefore cannot make the
    // array constexpr, if we could we could use:
    // static constexpr const auto &length = responses[static_cast<int>(CommandTypes::pin)].length();
    static constexpr const auto length = 8; // "OKsetpin" length
    // Send command to UC06
    bool wasSuccessful = sendCommand<pinSize, length>(CommandTypes::pin, newPincode);

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
    // Get the length of the expected response message
    // We cannot use the responses array because hwlib::string has no constexpr constructor (yet) and therefore cannot make the
    // array constexpr, if we could we could use:
    // static constexpr const auto &length = responses[static_cast<int>(CommandTypes::baud)].length();
    static constexpr const auto length = 2; // "OK" length
    // Send command to UC06
    bool wasSuccessful = sendCommand<baudrateSize, length>(CommandTypes::baud, BaudRateStrings[static_cast<int>(baud)],
                                                           BaudRateValues[static_cast<int>(baud)]);

    // Change name if it was successful
    if (wasSuccessful) {
        baudrate = baud;
    }

    return wasSuccessful;
}

void HC06::setVisibility(bool visible) {
    hwlib::cout << "Set visibility\n";
}