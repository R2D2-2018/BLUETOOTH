#ifndef BLUETOOTH_H
#define BLUETOOTH_H

#include "wrap-hwlib.hpp"
#include <string>

class bluetooth {
  public:
    /**
     * @brief Used to connect to other devices.
     * [BLANK]
     * Connect to the specified device ID. To get the device ID use function "search".
     * [BLANK]
     * @param[in]     deviceID    An unique ID of a device.
     * @return void
     */
    virtual void connect(int deviceID) = 0;

    /**
     * @brief Used to disconnect from other devices.
     * @return void
     */
    virtual void disconnect() = 0;

    /**
     * @brief Used to read the name of this device.
     * [BLANK]
     * This function will read the current device name and return an array with characters.
     * [BLANK]
     * @return string with the name.
     */
    virtual std::string getName() = 0;

    /**
     * @brief Used to read the status of the HC-06 chip.
     * [BLANK]
     * This function will check if the chip is detected and functional by performing a simple communication test.
     * [BLANK]
     * @return Int of current status.
     */
    virtual int getStatus() = 0;

    /**
     * @brief Used to get the current baudrate of this device.
     * [BLANK]
     * [BLANK]
     * This function will return the current baudrate used.
     * @return string with the name.
     */
    virtual unsigned int getBaud() = 0;

    /**
     * @brief Used to pair with other devices.
     * [BLANK]
     * Pair with the specified device ID. To get the device ID use function "search".
     * [BLANK]
     * @param[in]     deviceID    An unique ID of a device.
     * @return void
     */
    virtual void pair(int deviceID) = 0;

    /**
     * @brief Used to retrieve the message.
     * [BLANK]
     * Provide this function with own data buffer. The buffer will hold the received message.
     * [BLANK]
     * @param[in]     deviceID    An unique ID of a device.
     * @return void
     */
    virtual void receive(uint8_t *data) = 0;

    /**
     * @brief Used to discover any discoverable devices.
     * [BLANK]
     * This function will return a device id for all discovered devices. Use this ID to connect.
     * [BLANK]
     * @return uint8_t pointer to an array of unique device ID's.
     */
    virtual uint8_t *search() = 0;

    /**
     * @brief Used to send data to other devices.
     * [BLANK]
     * This function will send the data provided.
     * [BLANK]
     * @param[in]     data    A pointer to a uint8_t data array.
     * @return void
     */
    virtual void send(uint8_t *data) = 0;

    /**
     * @brief Used to set the baud rate of the connection.
     * @param[in]     baud    An integer specifying the baud rate.
     * @return void
     */
    virtual void setBaud(unsigned int & baud) = 0;

    /**
     * @brief Used to set the name of the chip. This is not an ID
     * @param[in]     name    A reference to the string containing the new name.
     * @return void
     */
    virtual void setName(const std::string & newName) = 0;

    /**
     * @brief choose whether the chip will be discoverable or not.
     * @param[in]     visible    An boolean to set the visibility.
     * @return void
     */
    virtual void setVisibility(bool visible) = 0;
};

#endif