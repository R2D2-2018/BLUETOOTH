/**
 * @file hc-05.hpp
 * @brief control the HC05 bluetooth module
 * @author HU R2D2 2018
 * @license see LICENSE
 */

#ifndef HC05_HPP
#define HC05_HPP

#include "uart_lib.hpp"
#include "wrap-hwlib.hpp"
#include <array>

class HC05 {
  public:
    ///< The different baudrate indices
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

    ///< CommandTypes available for the HC-05
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
        bind,
        initspp
    }; ///< Used by sendCommand to create a commandString

    const std::array<hwlib::string<7>, 12> BaudRateValues = {
        {"1200", "2400", "4800", "9600", "19200", "38400", "57600", "115200", "230400", "460800", "921600", "1382400"}};
    const std::array<hwlib::string<1>, 13> numberStrings = {{"0", "1", "2", "3", "4", "5", "6", "7", "8", "9", "A", "B", "C"}};
    const std::array<hwlib::string<maxNameSize>, 14> commands = {
        {"AT", "AT+NAME=", "AT+PSWD=", "AT+UART=", "AT+LINK=", "AT+DISC", "AT+CMODE=", "AT+ORGL",
         "AT+FSAD=", "AT+PAIR=", "AT+ROLE=", "AT+RESET", "AT+BIND=", "AT+INIT"}};
    BaudRates baudrate = BaudRates::SIX;

    UARTLib::UARTConnection &connection;
    hwlib::string<maxNameSize> name; ///< Used for storing the name of this device.
    hwlib::string<pinSize> pincode;  ///< Used for storing a local version of the 4 digit pincode saved as a byte
    bool mode = 1;
    hwlib::pin_out &select; ///< Pin used to change the HC05 from the slave loop into the AT-command mode
    hwlib::pin_out &power;  ///< Pin used to interupt the power to the HC05 for a second to boot back into AT-command mode

  private:
    /**
     * @brief Compare two strings
     *
     * Compare two strings character per character and see if they are the same
     *
     * @tparam      size    Length of the input strings
     * @param[in]   string1 The first string
     * @param[in]   string2 The second string
     * @return      true    Strings are the same
     * @retrun      false   Strings differ
     */
    template <size_t size>
    bool compareString(const hwlib::string<size> &string1, const hwlib::string<size> &string2) {
        for (size_t i = 0; i < size; ++i) {
            if (string1[i] != string2[i]) {
                return false;
            }
        }
        return true;
    }
    /**
     * @brief Check response for acknowledgement
     *
     * Check if a received message contains an acknowledgement
     *
     * @tparam      size    Length of the input string
     * @param[in]   string  Message to check
     * @return      true    Message contains acknowledgement
     * @return      false   Message does not contain acknowledgement
     */
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

    /**
     * @brief Send a command to the HC-05
     *
     * Send one of the predefined commands to the HC-05
     *
     * @tparam      size    Length of the data string
     * @param[in]   command Type The command that needs to be sent
     * @param[in]   data    The data that comes with the command
     * @param[in]   timeout The time before the command times out in us
     * @return      true    Message was sent successfully
     * @return      false   Message was not sent successfully
     */
    template <size_t size>
    bool sendCommand(CommandTypes commandType, hwlib::string<size> data = "", uint64_t timeout = 1'000'000) {
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
        auto result = receive<maxMessageSize>(timeout);

        // Check if respose is as expected
        return findAcknowledgement<maxMessageSize>(result);
    }

  public:
    HC05(UARTLib::UARTConnection &connection, hwlib::pin_out &initselect, hwlib::pin_out &initpower);

    /**
     * @brief Test if device is connected.
     *
     * Send a command to the HC-05 to see if it is connected to another device.
     *
     * @return  true    Device is connected
     * @return  false   Device is not connected
     */
    bool testConnection();

    /**
     * @brief Used to connect to other devices.
     *
     * Connect to the specified device ID.
     *
     * @param[in]     deviceID    An unique ID of a device.
     */
    bool connect(const hwlib::string<maxMessageSize> &deviceID);

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
     * @return True if set has succeeded and false if not
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
     * @return True if set has succeeded and false if not
     */
    bool setPincode(hwlib::string<pinSize> newPincode);

    /**
     * @brief Used to pair with other devices.
     *
     * Pair with the specified device ID.
     *
     * @param[in]     deviceID    An unique ID of a device.
     * @return True if set has succeeded and false if not
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
        volatile auto start = hwlib::now_us();
        while (static_cast<size_t>(connection.char_available()) < size && hwlib::now_us() - start < timeOut) {
            // hwlib::cout << connection.char_available();
        }

        // Write data to string
        for (unsigned int i = 0; i < size; i++) {
            if (connection.char_available()) {
                result[i] = connection.getc();
                // hwlib::cout << connection.getc() << hwlib::endl;
            }
        }

        // Clear uart buffer
        start = hwlib::now_us();
        while (hwlib::now_us() - start < timeOut) {
            connection.getc(); // Without this the compiler will remove the loop
            // hwlib::cout << "Test" << hwlib::endl;
        }
        for (size_t i = 0; i < connection.char_available(); ++i) {
            connection.getc();
        }

        return result;
    }

    /**
     * @brief Used to send data to other devices.
     *
     * This function will send the data provided.
     *
     * @param[in]     msg   a hwlib::string containing the message.
     */
    void send(const hwlib::string<maxMessageSize> &msg);

    /**
     * @brief Used to get the current baudrate of this device.
     *
     * This function will return the current baudrate used.
     * @return hwlib::string containing the baudrate
     */
    hwlib::string<7> getBaud();

    /**
     * @brief Used to set the baud rate of the connection.
     *
     * @param[in]     baud    An integer specifying the baud rate.
     * @return True if set has succeeded and false if not
     */
    bool setBaud(BaudRates baud);

    /**
     * @brief Used to set the mode/mode pin of the HC05
     *
     * @param[in]    bool saying if the chip has to be master or not
     */
    void setMode(bool master);

    /**
     * @brief returns current mode
     *
     * @return bool saying if the chip has to be master or not
     */
    bool getMode();

    /**
     * @brief function returning the received data as a string
     *
     * @param[in] uint64_t containing the timeout time that will be used
     * @return hwlib::string containing the received data
     */
    hwlib::string<maxMessageSize> receiveData(uint64_t timeout = 1'000'000);

    /**
     * @brief function returning the length of the received data
     *
     * @param[in] hwlib::string containing the data of which you want the length
     * @return an integer telling you what the current size of the string is
     */
    int checkDataLength(const hwlib::string<HC05::maxMessageSize> &data);

    /**
     * @brief function returning the version of the chip as a string
     *
     * @return hwlib::string containing the received data + acknowledgement
     */
    hwlib::string<maxMessageSize> getVersion();

    /**
     * @brief function setting the connectmode of the chip
     *
     * @param[in] the mode you want to use as an integer. see datasheet for more info.
     * @return True if chip acknowlegdes the command, false if failed
     */
    bool setConnectMode(int mode);

    /**
     * @brief function that resets all settings set by the AT commands
     *
     * @return True if chip acknowlegdes the command, false if failed
     */
    bool resetSettings();

    /**
     * @brief function that searches if the device is in the autheticated device list.
     *
     * @param[in] hwlib::string containing the deviceID of the chip you want to look up
     * @return True if chip acknowlegdes the command, false if failed
     */
    bool searchAuthenticatedDevice(const hwlib::string<maxMessageSize> &deviceID);

    /**
     * @brief function setting the role of the chip
     *
     * @param[in] the role you want to use as an integer. see datasheet for more info.
     * @return True if chip acknowlegdes the command, false if failed
     */
    bool setRole(int role);

    /**
     * @brief function soft-resetting the chip, used after setting the role.
     *
     * @return True if chip acknowlegdes the command, false if failed
     */
    bool reset();

    /**
     * @brief function binding the chip to another device
     *
     * @param[in] hwlib::string containing the deviceID of the chip you want to bind to
     * @return True if chip acknowlegdes the command, false if failed
     */
    bool bind(const hwlib::string<maxMessageSize> &deviceID);

    /**
     * @brief function initializing the SPP profile lib. used if you want to connect to another device.
     *
     * @return True if chip acknowlegdes the command, false if failed
     */
    bool initSPP();

    /**
     * @brief function used for scanning devices
     *
     * @return hwlib::string containing the complete response of the HC05 chip.
     */
    hwlib::string<maxMessageSize> inquiryDevices();
};

#endif
