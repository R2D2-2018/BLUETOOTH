#include "UART_LIB/uart_connection.hpp"
#include "hc-06.hpp"
#include "wrap-hwlib.hpp"

int main() {
    WDT->WDT_MR = WDT_MR_WDDIS;
    hwlib::wait_ms(1000);
    UARTConnection bluetoothConnection(9600, UARTController::ONE);
    UARTConnection platformConnection(9600, UARTController::TWO);
    Bluetooth::HC06 bluetooth(bluetoothConnection);

    if (bluetooth.setBaud(Bluetooth::HC06::BaudRates::FOUR)) {
        hwlib::cout << "Set baudrate to: " << bluetooth.getBaud() << hwlib::endl;
    } else {
        hwlib::cout << "Could not set baudrate" << hwlib::endl;
    }

    if (bluetooth.setName("R2D2-B1")) {
        hwlib::cout << "Renamed module" << hwlib::endl;
    } else {
        hwlib::cout << "Could not rename module" << hwlib::endl;
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

    while (true) {
        if (bluetooth.isConnectedToBlueTooth()) {
            if (bluetoothConnection.available() > 0) {
                const auto data = bluetooth.receive<1>();

                switch (data[0]) {
                case 'F':
                    hwlib::cout << "Motor forward" << hwlib::endl;
                    platformConnection << "F";
                    break;
                case 'B':
                    hwlib::cout << "Motor backward" << hwlib::endl;
                    platformConnection << "B";
                    break;
                case 'R':
                    hwlib::cout << "Motor turn right" << hwlib::endl;
                    platformConnection << "R";
                    break;
                case 'L':
                    hwlib::cout << "Motor turn left" << hwlib::endl;
                    platformConnection << "L";
                    break;
                }
            }
        } else {
            hwlib::cout << bluetooth.getName() << ": " << ((bluetooth.testConnection()) ? "Connected" : "Not connected")
                        << hwlib::endl;
        }
    }
}
