#include "UART_LIB/uart_connection.hpp"
#include "hc-06.hpp"
#include "wrap-hwlib.hpp"

int main() {
    WDT->WDT_MR = WDT_MR_WDDIS;
    hwlib::wait_ms(1000);
    HC06 bluetooth;

    bluetooth.setName("R2D2-B1");

    while (true) {
        hwlib::cout << bluetooth.getName() << ": " << ((bluetooth.testConnection()) ? "Connected" : "Not connected") << hwlib::endl;
    }
}
