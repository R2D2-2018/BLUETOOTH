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
  public:
    enum class BaudRates {
        ONE = 0,
        TWO,
        THREE,
        FOUR, // DEFAULT
        FIVE,
        SIX,
        SEVEN,
        EIGHT,
        NINE,
        A,
        B,
        C
    };

  private:
    static constexpr const uint8_t maxNameSize = 50;
    static constexpr const uint8_t pinSize = 4;

    enum class CommandTypes { test = 0, name, pin, baud }; ///< Used by sendCommand to create a commandString

    const std::array<uint32_t, 12> BaudRateValues = {1200,  2400,   4800,   9600,   19200,  38400,
                                                     57600, 115200, 230400, 460800, 921600, 1382400};
    const std::array<hwlib::string<1>, 12> BaudRateStrings = {"1", "2", "3", "4", "5", "6", "7", "8", "9", "A", "B", "C"};
    const std::array<hwlib::string<maxNameSize>, 4> commands = {"AT", "AT+NAME", "AT+PIN", "AT+BAUD"};
    const std::array<hwlib::string<maxNameSize>, 4> responses = {"OK", "OKsetname", "OKsetpin", "OKsetbaud"};
    uint8_t discoveredDevices[32]; ///< Used for storing the connection id of a discovered device.
    BaudRates baudrate = BaudRates::FOUR;

    UARTConnection connection;
    hwlib::string<maxNameSize> name; ///< Used for storing the name of this device.
    hwlib::string<pinSize> pincode;  ///< Used for storing a local version of the 4 digit pincode saved as a byte
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

    template <size_t size>
    bool sendCommand(CommandTypes commandType, hwlib::string<size> data) {
        const auto &expectedResponseMessage = responses[static_cast<int>(commandType)];
        // Create command
        auto command = commands[static_cast<int>(commandType)];
        command += data;

        // Send command
        connection << command;

        // Get response
        // TODO: Try to get length to work, currently gives the value of 'expectedResponseMessage' is not usable in a constant
        // expression auto result = receive<expectedResponseMessage.length()>();
        auto result = receive<2>();

        // Check if respose is as expected
        return compareString<2>(result, expectedResponseMessage);
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
     * @brief Used to set the name of the chip. This is not an ID
     *
     * @param[in]     name    A reference to a string holding the name.
     */
    bool setName(const hwlib::string<50> &newName);

    /**
     * @brief Used to get the pin code of the device
     *
     * This function will return thecurrent device pincode.
     * The pincode is 4 digit and saved as a hwlib::string
     *
     * @return The pincode
     */
    hwlib::string<pinSize> getPincode();

    /**
     * @brief Used to set the pincode of the device.
     *
     * The pincode is 4 digit and saved as a hwlib::string
     *
     * @param[in]     newPincode    The new pincode
     */
    bool setPincode(hwlib::string<pinSize> newPincode);

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

        // Write data to string
        for (unsigned int i = 0; i < size; i++) {
            result[i] = connection.receive();
        }

        // Clear uart buffer
        while (hwlib::now_us() - start < timeOut) {
        }
        for (size_t i = 0; i < connection.available(); ++i) {
            connection.receive();
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
     * @brief Used to get the current baudrate of this device.
     *
     * This function will return the current baudrate used.
     */
    uint32_t getBaud();

    /**
     * @brief Used to set the baud rate of the connection.
     * @param[in]     baud    An integer specifying the baud rate.
     */
    bool setBaud(BaudRates baud);

    /**
     * @brief choose whether the chip will be discoverable or not.
     *
     * @param[in]     visible    An boolean to set the visibility.
     */
    void setVisibility(bool visible);
};

#endif
