#include "UART_LIB/uart_connection.hpp"
#include "hc-05.hpp"
#include "hc-06.hpp"
#include "wrap-hwlib.hpp"

int main() {
    WDT->WDT_MR = WDT_MR_WDDIS;
    hwlib::wait_ms(1000);
    UARTConnection connection(9600, UARTController::ONE);
    Bluetooth::HC06 bluetooth(connection);

    if (bluetooth.setBaud(Bluetooth::HC06::BaudRates::FOUR)) {
        hwlib::cout << "Set baudrate to: " << bluetooth.getBaud() << hwlib::endl;
    } else {
        hwlib::cout << "Could not set baudrate" << hwlib::endl;
    }

    if (bluetooth.setPincode("1234")) {
        hwlib::cout << "Set pincode to " << bluetooth.getPincode() << hwlib::endl;
    } else {
        hwlib::cout << "Could not set pin" << hwlib::endl;
    }

    if (bluetooth.setParityCheckMode(Bluetooth::HC06::ParityModes::NONE)) {
        hwlib::cout << "Set parityMode to " << static_cast<int>(bluetooth.getParityCheckMode()) << hwlib::endl;
    } else {
        hwlib::cout << "Could not set parity" << hwlib::endl;
    }

    constexpr size_t dataSize = 60;
    while (true) {
        if (bluetooth.isConnectedToBlueTooth()) {
            if (connection.available() > dataSize) {
                hwlib::cout << bluetooth.receive<dataSize>();
            }
        } else {
            hwlib::cout << bluetooth.getName() << ": " << ((bluetooth.testConnection()) ? "Connected" : "Not connected")
                        << hwlib::endl;
        }
    }
}
