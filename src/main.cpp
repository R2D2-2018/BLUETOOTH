#include "UART_LIB/uart_connection.hpp"
#include "hc-05.hpp"
#include "hc-06.hpp"
#include "wrap-hwlib.hpp"

int main() {
    WDT->WDT_MR = WDT_MR_WDDIS;
    hwlib::wait_ms(1000);
    HC05 bluetooth;

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
        bluetooth.send("msg");

        // hwlib::cout << bluetooth.getName() << ": " << ((bluetooth.testConnection()) ? "Connected" : "Not connected") <<
        // hwlib::endl;
    }
}
