#include "UART_LIB/uart_connection.hpp"
#include "hc-05.hpp"
#include "hc-06.hpp"
#include "wrap-hwlib.hpp"

int main() {
    WDT->WDT_MR = WDT_MR_WDDIS;
    hwlib::wait_ms(1000);

    UARTConnection connectionmaster(38400, UARTController::ONE);
    UARTConnection connectionslave(9600, UARTController::TWO);
    HC05 master(connectionmaster);
    // HC06 slave(connectionslave);

    // if (slave.setName("Gurneel")) {
    //     hwlib::cout << "Renamed module" << hwlib::endl;
    // } else {
    //     hwlib::cout << "Could not rename module" << hwlib::endl;
    // }

    // if (slave.setPincode("1234")) {
    //     hwlib::cout << "Set pincode to 1234" << hwlib::endl;
    // } else {
    //     hwlib::cout << "Could not set pin" << hwlib::endl;
    // }

    // if (slave.setBaud(HC06::BaudRates::FOUR)) {
    //     hwlib::cout << "Set baudrate to: " << slave.getBaud() << hwlib::endl;
    // } else {
    //     hwlib::cout << "Could not set baudrate" << hwlib::endl;
    // }

    master.setMode(1);
    hwlib::wait_ms(1000);
    hwlib::cout << master.resetSettings();
    hwlib::cout << master.setBaud(HC05::BaudRates::SIX);
    hwlib::cout << master.setPincode("1234");
    hwlib::cout << master.setConnectMode(0);
    hwlib::cout << master.setRole(1);
    hwlib::cout << master.reset();
    hwlib::cout << master.initSPP();
    hwlib::cout << master.pair("98D3,31,FC7389");
    hwlib::cout << master.bind("98D3,31,FC7389");
    hwlib::cout << master.connect("98D3,31,FC7389");
    // hwlib::cout << master.pair("98D3,31,FC6BE2");
    // hwlib::cout << master.bind("98D3,31,FC6BE2");
    // hwlib::cout << master.connect("98D3,31,FC6BE2");

    while (true) {
        char choice;
        hwlib::string<60> command;
        hwlib::cin >> choice;
        hwlib::cout << choice << hwlib::endl;
        if (choice == '1') {
            command = "CN";
        } else if (choice == '2') {
            command = "OK";
        } else if (choice == '3') {
            command = "\n  .=.\n '==c|\n [)-+|\n //'_|\n/]==;\\\nR2D2 2018 Team 4\n";
        } else if (choice == '4') {
            master.connect("98D3,31,FC7389");
        }
        hwlib::cout << command << hwlib::endl;
        master.send(command);
    }
}
