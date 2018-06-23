#include "UART_LIB/uart_connection.hpp"
#include "hc-05.hpp"
#include "hc-06.hpp"
#include "wrap-hwlib.hpp"

int main() {
    WDT->WDT_MR = WDT_MR_WDDIS;
    hwlib::wait_ms(1000);
    HC05 bluetooth;

    bluetooth.setMode(1);
    hwlib::wait_ms(1000);
    hwlib::cout << bluetooth.resetSettings();
    hwlib::cout << bluetooth.setBaud(HC05::BaudRates::FOUR);
    hwlib::cout << bluetooth.setConnectMode(0);
    hwlib::cout << bluetooth.setRole(1);
    hwlib::cout << bluetooth.reset();
    hwlib::cout << bluetooth.searchAuthenticatedDevice("98D3,31,FC7389");
    hwlib::cout << bluetooth.pair("98D3,31,FC7389");
    hwlib::cout << bluetooth.bind("98D3,31,FC7389");
    hwlib::cout << bluetooth.setConnectMode(1);
    hwlib::cout << bluetooth.connect("98D3,31,FC7389");
    // auto data = bluetooth.initSPP();
    // for (int i = 0; i < bluetooth.checkDataLength(data); i++) {
    //     hwlib::cout << data[i];
    // }
    // auto data2 = bluetooth.inquiryDevices();
    // for (int i = 0; i < bluetooth.checkDataLength(data2); i++) {
    //     hwlib::cout << data2[i];
    // }

    // if (bluetooth.setName("R2D2-B1")) {
    //     hwlib::cout << "Renamed module" << hwlib::endl;
    // } else {
    //     hwlib::cout << "Could not rename module" << hwlib::endl;
    // }

    // if (bluetooth.setPincode("1234")) {
    //     hwlib::cout << "Set pincode to 1234" << hwlib::endl;
    // } else {
    //     hwlib::cout << "Could not set pin" << hwlib::endl;
    // }

    // if (bluetooth.setBaud(HC06::BaudRates::FOUR)) {
    //     hwlib::cout << "Set baudrate to: " << bluetooth.getBaud() << hwlib::endl;
    // } else {
    //     hwlib::cout << "Could not set baudrate" << hwlib::endl;
    // }

    while (true) {
        // auto data = bluetooth.getVersion();
        // for (int i = 0; i < bluetooth.checkDataLength(data); i++) {
        //     hwlib::cout << data[i];
        // }
        // hwlib::cout << bluetooth.getName() << ": " << ((bluetooth.testConnection()) ? "Connected" : "Not connected") <<
        // hwlib::endl;
    }
}
