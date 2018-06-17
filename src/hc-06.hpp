/**
 * @file hc-06.hpp
 * @brief control the hc06 bluetooth module
 * @author HU R2D2 2018
 * @license see LICENSE
 */

#ifndef HC06_H
#define HC06_H

#include "UART_LIB/uart_connection.hpp"
#include "wrap-hwlib.hpp"
#include <array>

class HC06 {
  private:
    static constexpr const uint8_t maxNameSize = 50;
    uint8_t discoveredDevices[32]; ///< Used for storing the connection id of a discovered device.
    unsigned int currentBaudrate;
    UARTConnection connection;
    hwlib::string<maxNameSize> name; ///< Used for storing the name of this device.
  private:
    template <size_t size>
    bool compareString(const hwlib::string<size> &string1, const hwlib::string<size> &string2) {
        for (size_t i = 0; i < size; ++i) {
            if (string1[i] != string2[i]) {
                return false;
            }
        }

        return true;
    }

  public:
    HC06();

    bool testConnection();

    /**
     * @brief Used to connect to other devices.
     *
     * Connect to the specified device ID. To get the device ID use function "search".
     *
     * @param[in]     deviceID    An unique ID of a device.
     */
    void connect(int deviceID);

    /**
     * @brief Used to disconnect from other devices.
     */
    void disconnect();

    /**
     * @brief Used to read the name of this device.
     *
     * This function will read the current device name and return a string.
     *
     * @return string with the name.
     */
    hwlib::string<maxNameSize> getName();

    /**
     * @brief Used to read the status of the HC-06 chip.
     *
     * This function will check if the chip is detected and functional by performing a simple communication test.
     *
     * @return Int of current status.
     */
    int getStatus();

    /**
     * @brief Used to pair with other devices.
     *
     * Pair with the specified device ID. To get the device ID use function "search".
     *
     * @param[in]     deviceID    An unique ID of a device.
     */
    void pair(int deviceID);

    /**
     * @brief Used the uart connection to receive a message
     *
     * This function waits until the uart available is the size of the message or when it timesOut.
     * Then it creates a hwlib::string and filles it with the message and returns it.
     *
     * @tparam        size        The size of result string
     * @param[in]     timeOut     Number of us before the function times out
     * @return The hwlib::string with the reveived data
     */
    template <int size>
    hwlib::string<size> receive(uint_fast64_t timeOut = 1'000'000) {
        hwlib::string<size> result;

        // Wait for response, timeout at when it takes to long
        auto start = hwlib::now_us();
        while (connection.available() < size && hwlib::now_us() - start < timeOut) {
            // hwlib::cout << connection.available();
        }
        for (unsigned int i = 0; i <= connection.available(); i++) {
            result[i] = connection.receive();
        }

        return result;
    }

    /**
     * @brief Used to discover any discoverable devices.
     *
     * This function will return a device id for all discovered devices. Use this ID to connect.
     *
     * @return uint8_t pointer to an array of unique device ID's.
     */
    uint8_t *search();

    /**
     * @brief Used to send data to other devices.
     *
     * This function will send the data provided.
     *
     * @param[in]     data    A pointer to a uint8_t data array.
     */
    void send(uint8_t *data);

    /**
     * @brief Used to set the baud rate of the connection.
     * @param[in]     baud    An integer specifying the baud rate.
     */
    void setBaud(const unsigned int &baud);

    /**
     * @brief Used to get the current baudrate of this device.
     *
     *
     * This function will return the current baudrate used.
     * @return string with the name.
     */
    unsigned int getBaud();

    /**
     * @brief Used to set the name of the chip. This is not an ID
     *
     * @param[in]     name    A reference to a string holding the name.
     */
    bool setName(const hwlib::string<50> &newName);

    /**
     * @brief choose whether the chip will be discoverable or not.
     *
     * @param[in]     visible    An boolean to set the visibility.
     */
    void setVisibility(bool visible);
};

#endif
