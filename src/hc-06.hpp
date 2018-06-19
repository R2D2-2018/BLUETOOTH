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
    enum class BaudRates { ///< Used by the setBaud method to set the baudrates
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
    ///< Used for UART connection
    UARTConnection connection;

    ///< Used by get and set name for hwlib::string
    static constexpr const uint8_t maxNameSize = 50;
    ///< Used by get and set pin for hwlib::string
    static constexpr const uint8_t pinSize = 4;
    ///< Used by get and set pin for hwlib::string
    static constexpr const uint8_t baudrateSize = 1;
    ///< Used by sendCommand to create a commandString
    enum class CommandTypes { test = 0, name, pin, baud };

    ///< Used to convert BaudRates to value
    const std::array<uint32_t, 12> BaudRateValues = {1200,  2400,   4800,   9600,   19200,  38400,
                                                     57600, 115200, 230400, 460800, 921600, 1382400};
    ///< Used to convert BaudRates to string
    const std::array<hwlib::string<baudrateSize>, 12> BaudRateStrings = {"1", "2", "3", "4", "5", "6",
                                                                         "7", "8", "9", "A", "B", "C"};
    ///< Used by sendCommand method to send commands to UC06 device
    const std::array<hwlib::string<maxNameSize>, 4> commands = {"AT", "AT+NAME", "AT+PIN", "AT+BAUD"};
    ///< Used by sendCommand method to validate response
    const std::array<hwlib::string<maxNameSize>, 4> responses = {"OK", "OKsetname", "OKsetPIN", "OK"};

    uint8_t discoveredDevices[32];        ///< Used for storing the connection id of a discovered device.
    BaudRates baudrate = BaudRates::FOUR; ///< Used for the baudrate
    hwlib::string<maxNameSize> name;      ///< Used for storing the name of this device.
    hwlib::string<pinSize> pincode;       ///< Used for storing a local version of the 4 digit pincode saved as a byte
  private:
    /*
     * @brief convert uint32_t to hwlib::string
     *
     * Removes 0's before the first non zero value
     *
     * @param The number that needs to be converted
     * @return The number in string format
     */
    hwlib::string<0> uint32_tToString(uint32_t number) {
        // 4294967296 = max 32u = 10 digits
        hwlib::string<10> str = "          ";
        // Convert number to inverted string
        for (uint8_t i = 0; i < 10; ++i) {
            str[i] = static_cast<char>(number % 10 + '0');
            number /= 10;
        }

        // Put string in right order
        for (uint8_t i = 0; i < str.length() / 2; ++i) {
            const auto tmp = str[i];
            str[i] = str[str.length() - 1 - i];
            str[str.length() - 1 - i] = tmp;
        }

        // Remove trailing zerors
        hwlib::string<10> nonZeroString;
        bool foundFirstNonZero = false;
        for (const auto &st : str) {
            if (!foundFirstNonZero && st != '0') {
                foundFirstNonZero = true;
            }
            if (foundFirstNonZero) {
                nonZeroString += st;
            }
        }
        return nonZeroString;
    }

    /*
     * @brief compares to hwlib::strings
     *
     * @return True if equal, false if not
     */
    template <size_t size>
    bool compareString(const hwlib::string<size> &string1, const hwlib::string<size> &string2) {
        for (size_t i = 0; i < size; ++i) {
            hwlib::cout << string1[i] << ", " << string2[i] << hwlib::endl;
            if (string1[i] != string2[i]) {
                return false;
            }
        }

        return true;
    }

    /*
     * @brief Sends command to device using UART
     *
     * Uses the commandType to create a command with the given data, then sends it
     * The uses the reveive method to check for response of the decive and checks if the command was successfully set
     *
     * @tparam     size          Size of the data string
     * @param      commandType   The command type of the command that needs to be send
     * @param      data          The data that needs to be send
     * @return If the command was successfully received at the device
     */
    template <size_t size, size_t responseSize>
    bool sendCommand(CommandTypes commandType, hwlib::string<size> data, uint32_t baudrate = 0) {
        auto expectedResponseMessage = responses[static_cast<int>(commandType)];

        // The baudrate resonse adds the baud rate after the message
        if (baudrate != 0) {
            expectedResponseMessage += uint32_tToString(baudrate);
        }

        // Create command
        auto command = commands[static_cast<int>(commandType)];
        command += data;

        // Send command
        connection << command;

        // Get response
        // expression auto result = receive<expectedResponseMessage.length()>();
        auto result = receive<responseSize>();

        // Check if respose is as expected
        return compareString<responseSize>(result, expectedResponseMessage);
    }

  public:
    HC06();

    /*
     * @brief Tests if there is a connection with the device
     *
     * Sends the "AT" command and checks if the device responds with "OK"
     *
     * @return True if there is a connection, else false
     */
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
            if (connection.available()) {
                result[i] = connection.receive();
                // hwlib::cout << connection.receive() << hwlib::endl;
            }
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
