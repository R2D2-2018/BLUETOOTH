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

HC06::HC06(){}

void HC06::connect(int deviceID){
    hwlib::cout << "Connect to device: " << deviceID << '\n';
}

void HC06::disconnect(){
    hwlib::cout << "Disconnect\n";
}

uint8_t* HC06::getName(){
    hwlib::cout << "Get name\n";
    return name;
}

int HC06::getStatus(){
    hwlib::cout << "Get status\n";
    return 0;
}

void HC06::pair(int deviceID){
    hwlib::cout << "Pair with device: " << deviceID << '\n';
}

void HC06::receive(uint8_t *data){
    hwlib::cout << "Receive data\n";
}

uint8_t* HC06::search(){
    hwlib::cout << "Search for devices\n";
    return discoveredDevices;
}

void HC06::send(uint8_t *data){
    hwlib::cout << "Sending data\n";
}

void HC06::setBaud(int baud){
    hwlib::cout << "Set baud rate to: " << baud << '\n';
}

void HC06::setName(const uint8_t *name){
    hwlib::cout << "Set name\n";
}

void HC06::setVisibility(bool visible){
    hwlib::cout << "Set visibility\n";
}