#include "UART_LIB/uart_connection.hpp"
#include "hc-06.hpp"
#include "wrap-hwlib.hpp"

int main() {
    WDT->WDT_MR = WDT_MR_WDDIS;
    hwlib::wait_ms(1000);
    UARTConnection connection(9600, UARTController::ONE);
    HC06 bluetooth(connection);

    if (bluetooth.setName("R2D2-B1")) {
        hwlib::cout << "Renamed module" << hwlib::endl;
    } else {
        hwlib::cout << "Could not rename module" << hwlib::endl;
    }

    if (bluetooth.setPincode("1234")) {
        hwlib::cout << "Set pincode to 1234" << hwlib::endl;
    } else {
        hwlib::cout << "Could not set pin" << hwlib::endl;
    }

    if (bluetooth.setBaud(HC06::BaudRates::FOUR)) {
        hwlib::cout << "Set baudrate to: " << bluetooth.getBaud() << hwlib::endl;
    } else {
        hwlib::cout << "Could not set baudrate" << hwlib::endl;
    }

    if (bluetooth.setParityCheckMode(HC06::ParityModes::NONE)) {
        hwlib::cout << "Set parityMode to " << static_cast<int>(bluetooth.getParityCheckMode()) << hwlib::endl;
    } else {
        hwlib::cout << "Could not set parity" << hwlib::endl;
    }

    while (true) {
        hwlib::cout << bluetooth.getName() << ": " << ((bluetooth.testConnection()) ? "Connected" : "Not connected") << hwlib::endl;
    }
}
