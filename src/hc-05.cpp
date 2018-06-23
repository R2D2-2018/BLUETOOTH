#include "hc-05.hpp"

HC05::HC05() : connection(38400, UARTController::ONE) {
    power.set(1);
    setMode(mode);
}

bool HC05::testConnection() {
    return sendCommand<maxMessageSize>(CommandTypes::test);
}

bool HC05::connect(hwlib::string<maxMessageSize> deviceID) {
    if (searchAuthenticatedDevice(deviceID)) {
        return sendCommand<maxMessageSize>(CommandTypes::connect, deviceID);
    }
    return false;
}

bool HC05::disconnect() {
    return sendCommand<maxMessageSize>(CommandTypes::disconnect);
}

hwlib::string<HC05::maxNameSize> HC05::getName() {
    return name;
}

bool HC05::setName(const hwlib::string<maxNameSize> &newName) {
    // Send command to UC06
    bool wasSuccessful = sendCommand<maxNameSize>(CommandTypes::name, newName);

    // Change name if it was successful
    if (wasSuccessful) {
        name = newName;
    }

    return wasSuccessful;
}

hwlib::string<HC05::pinSize> HC05::getPincode() {
    return pincode;
}

bool HC05::setPincode(hwlib::string<pinSize> newPincode) {
    // Send command to UC06
    bool wasSuccessful = sendCommand<maxNameSize>(CommandTypes::pin, newPincode);

    // Change name if it was successful
    if (wasSuccessful) {
        pincode = newPincode;
    }

    return wasSuccessful;
}

bool HC05::pair(hwlib::string<maxMessageSize> deviceID) {
    deviceID += ", 9";
    return sendCommand<maxMessageSize>(CommandTypes::pair, deviceID);
}

void HC05::send(hwlib::string<maxMessageSize> msg) {
    connection << msg;
}

hwlib::string<7> HC05::getBaud() {
    return BaudRateValues[static_cast<uint32_t>(baudrate)];
}

bool HC05::setBaud(BaudRates baud) {
    // Send command to UC06
    hwlib::string<maxMessageSize> cmd = BaudRateValues[static_cast<int>(baud)];
    cmd += ",1,2";
    bool wasSuccessful = sendCommand<maxMessageSize>(CommandTypes::baud, cmd);

    // Change name if it was successful
    if (wasSuccessful) {
        baudrate = baud;
    }

    return wasSuccessful;
}

void HC05::setMode(int master) {
    mode = master;
    select.set(mode);
    power.set(0);
    hwlib::wait_ms(1000);
    power.set(1);
}

int HC05::getMode() {
    return mode;
}

hwlib::string<HC05::maxMessageSize> HC05::receiveData() {
    auto data = receive<HC05::maxMessageSize>();
    return data;
}

int HC05::checkDataLength(hwlib::string<HC05::maxMessageSize> data) {
    int size = 0;
    while (data[size] != 255) {
        size++;
    }
    return size;
}

hwlib::string<HC05::maxMessageSize> HC05::getVersion() {
    connection << "AT+VERSION?\r\n";
    auto data = receiveData();
    return data;
}

bool HC05::setConnectMode(int mode) {
    return sendCommand<maxMessageSize>(CommandTypes::connectmode, numberStrings[mode]);
}

bool HC05::resetSettings() {
    return sendCommand<maxMessageSize>(CommandTypes::restore);
}

bool HC05::searchAuthenticatedDevice(hwlib::string<maxMessageSize> deviceID) {
    return sendCommand<maxMessageSize>(CommandTypes::fsad, deviceID);
}

bool HC05::setRole(int role) {
    return sendCommand<maxMessageSize>(CommandTypes::role, numberStrings[role]);
}

bool HC05::reset() {
    return sendCommand<maxMessageSize>(CommandTypes::reset);
}

bool HC05::bind(hwlib::string<maxMessageSize> deviceID) {
    return sendCommand<maxMessageSize>(CommandTypes::bind, deviceID);
}

hwlib::string<HC05::maxMessageSize> HC05::initSPP() {
    connection << "AT+INIT\r\n";
    auto data = receiveData();
    return data;
}

hwlib::string<HC05::maxMessageSize> HC05::inquiryDevices() {
    connection << "AT+INQM=1,9,1\r\n";
    connection << "AT+INQ\r\n";
    auto data = receiveData();
    return data;
}