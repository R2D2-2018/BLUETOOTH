/**
 * @file hc-05.hpp
 * @brief control the HC05 bluetooth module
 * @author HU R2D2 2018
 * @license see LICENSE
 */

#ifndef HC05_HPP
#define HC05_HPP

#include "UART_LIB/uart_connection.hpp"
#include "wrap-hwlib.hpp"
#include <array>

class HC05 {
  public:
    enum class BaudRates {
        ONE = 1,
        TWO,
        THREE,
        FOUR,
        FIVE,
        SIX, // DEFAULTHC05
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
    static constexpr const uint8_t maxMessageSize = 60;

    enum class CommandTypes {
        test = 0,
        name,
        pin,
        baud,
        connect,
        disconnect,
        connectmode,
        restore,
        fsad,
        pair,
        role,
        reset,
        bind
    }; ///< Used by sendCommand to create a commandString

    const std::array<hwlib::string<7>, 12> BaudRateValues = {"1200",  "2400",   "4800",   "9600",   "19200",  "38400",
                                                             "57600", "115200", "230400", "460800", "921600", "1382400"};
    const std::array<hwlib::string<1>, 13> numberStrings = {"0", "1", "2", "3", "4", "5", "6", "7", "8", "9", "A", "B", "C"};
    const std::array<hwlib::string<maxNameSize>, 13> commands = {
        "AT",      "AT+NAME=", "AT+PSWD=", "AT+UART=", "AT+LINK=", "AT+DISC", "AT+CMODE=",
        "AT+ORGL", "AT+FSAD=", "AT+PAIR=", "AT+ROLE=", "AT+RESET", "AT+BIND="};
    // const std::array<hwlib::string<maxNameSize>, 4> responses = {"OK", "OKsetname", "OKsetpin", "OKsetbaud"};
    // uint8_t discoveredDevices[32]; ///< Used for storing the connection id of a discovered device.
    BaudRates baudrate = BaudRates::SIX;

    UARTConnection connection;
    hwlib::string<maxNameSize> name; ///< Used for storing the name of this device.
    hwlib::string<pinSize> pincode;  ///< Used for storing a local version of the 4 digit pincode saved as a byte
    int mode = 1;
    hwlib::target::pin_out select = hwlib::target::pin_out(hwlib::target::pins::d22);
    hwlib::target::pin_out power = hwlib::target::pin_out(hwlib::target::pins::d24);

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
    bool findAcknowledgement(const hwlib::string<size> &string) {
        for (size_t i = 0; i < size; ++i) {
            if (string[i] == 'O') {
                if (string[i + 1] == 'K') {
                    return true;
                }
            }
        }
        return false;
    }

    template <size_t size>
    bool sendCommand(CommandTypes commandType, hwlib::string<size> data = "") {
        // const auto &expectedResponseMessage = responses[static_cast<int>(commandType)];
        // Create command
        auto command = commands[static_cast<int>(commandType)];
        data += "\r\n";
        command += data;

        // Send command
        connection << command;

        // Get response
        // TODO: Try to get length to work, currently gives the value of 'expectedResponseMessage' is not usable in a constant
        // expression auto result = receive<expectedResponseMessage.length()>();
        auto result = receive<maxMessageSize>();
        auto acknowledgement = findAcknowledgement<maxMessageSize>(result);

        // Check if respose is as expected
        return acknowledgement;
    }

  public:
    HC05();

    bool testConnection();

    /**
     * @brief Used to connect to other devices.
     *
     * Connect to the specified device ID. To get the device ID use function "search".
     *
     * @param[in]     deviceID    An unique ID of a device.
     */
    bool connect(hwlib::string<maxMessageSize> deviceID);

    /**
     * @brief Used to disconnect from other devices.
     */
    bool disconnect();

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
    bool pair(hwlib::string<maxMessageSize> deviceID);

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
     * @brief Used to send data to other devices.
     *
     * This function will send the data provided.
     *
     * @param[in]     data    A pointer to a uint8_t data array.
     */
    void send(hwlib::string<maxMessageSize> msg);

    /**
     * @brief Used to get the current baudrate of this device.
     *
     * This function will return the current baudrate used.
     */
    hwlib::string<7> getBaud();

    /**
     * @brief Used to set the baud rate of the connection.
     * @param[in]     baud    An integer specifying the baud rate.
     */
    bool setBaud(BaudRates baud);

    void setMode(int master);

    int getMode();

    hwlib::string<maxMessageSize> receiveData();

    int checkDataLength(hwlib::string<HC05::maxMessageSize> data);

    hwlib::string<maxMessageSize> getVersion();

    bool setConnectMode(int mode);

    bool resetSettings();

    bool searchAuthenticatedDevice(hwlib::string<maxMessageSize> deviceID);

    bool setRole(int role);

    bool reset();

    bool bind(hwlib::string<maxMessageSize> deviceID);

    hwlib::string<HC05::maxMessageSize> initSPP();

    hwlib::string<maxMessageSize> inquiryDevices();
};

#endif
