// ==========================================================================
//
// File      : hc-06.cpp
// Part of   : C++ library for using the hc-06 bluetooth module.
//
// ==========================================================================

// this file contains Doxygen lines
/**
 * @author HU R2D2 2018
 * @date 13/05/2018
 * @file hc-06.cpp
 */

#include "hc-06.hpp"

HC06::HC06() {
}

void HC06::connect(int deviceID) {
    hwlib::cout << "Connect to device: " << deviceID << '\n';
}

void HC06::disconnect() {
    hwlib::cout << "Disconnect\n";
}

std::string HC06::getName() {
    hwlib::cout << "Get name\n";
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

void HC06::setName(const std::string &newName) {
    name = newName;
    // uart-comm stuff to send new name (max 20 chars)
}

void HC06::setVisibility(bool visible) {
    hwlib::cout << "Set visibility\n";
}