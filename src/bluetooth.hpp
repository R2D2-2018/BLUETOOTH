#ifndef BLUETOOTH_H
#define BLUETOOTH_H

#include "wrap-hwlib.hpp"

class Bluetooth {
  protected:
    hwlib::string<50> name; ///< Used for storing the name of this device.
  public:
    Bluetooth() {
    }
    /**
     * @brief Used to connect to other devices.
     *
     * Connect to the specified device ID. To get the device ID use function "search".
     *
     * @param[in]     deviceID    An unique ID of a device.
     */
    virtual void connect(int deviceID) = 0;

    /**
     * @brief Used to disconnect from other devices.
     */
    virtual void disconnect() = 0;

    /**
     * @brief Used to read the name of this device.
     *
     * This function will read the current device name and return an array with characters.
     *
     * @return string with the name.
     */
    virtual hwlib::string<50> getName() = 0;

    /**
     * @brief Used to read the status of the HC-06 chip.
     *
     * This function will check if the chip is detected and functional by performing a simple communication test.
     *
     * @return Int of current status.
     */
    virtual int getStatus() = 0;

    /**
     * @brief Used to get the current baudrate of this device.
     *
     * This function will return the current baudrate used.
     *
     * @return string with the name.
     */

    virtual void pair(int deviceID) = 0;

    /**
     * @brief Used to retrieve the message.
     *
     * Provide this function with own data buffer. The buffer will hold the received message.
     *
     * @param[in]     deviceID    An unique ID of a device.
     */
    virtual void receive(uint8_t *data) = 0;

    /**
     * @brief Used to discover any discoverable devices.
     *
     * This function will return a device id for all discovered devices. Use this ID to connect.
     *
     * @return Pointer to an array of unique device ID's.
     */
    virtual uint8_t *search() = 0;

    /**
     * @brief Used to send data to other devices.
     *
     * This function will send the data provided.
     *
     * @param[in]     data    A pointer to a uint8_t data array.
     */
    virtual void send(uint8_t *data) = 0;

    /**
     * @brief Used to set the baud rate of the connection.
     *
     * @param[in]     baud    An integer specifying the baud rate.
     */
    virtual void setBaud(const unsigned int &baud) = 0;

    /**
     * @brief Used to set the name of the chip. This is not an ID
     * @param[in]     name    A reference to the string containing the new name.
     */
    virtual unsigned int getBaud() = 0;

    /**
     * @brief Used to pair with other devices.
     *
     * Pair with the specified device ID. To get the device ID use function "search".
     *
     * @param[in]     deviceID    An unique ID of a device.
     */
    virtual void setName(const hwlib::string<50> &newName) = 0;

    /**
     * @brief choose whether the chip will be discoverable or not.
     *
     * @param[in]     visible    An boolean to set the visibility.
     */
    virtual void setVisibility(bool visible) = 0;
};

#endif