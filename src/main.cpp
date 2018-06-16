#include "hc-06.hpp"
#include "wrap-hwlib.hpp"

int main() {
    WDT->WDT_MR = WDT_MR_WDDIS;

    hwlib::wait_ms(1000);
    hwlib::cout << "Hello world!" << hwlib::endl;

    HC06 bluetooth;
    bluetooth.setName("R2D2-b1");

    while (true) {
        hwlib::cout << bluetooth.getName() << hwlib::endl;
        hwlib::wait_ms(1000);
    }

    return 0;
}
