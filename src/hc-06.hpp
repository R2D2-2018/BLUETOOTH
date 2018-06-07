/**
 * @class HC06
 * @author HU R2D2 2018
 * @date 13/05/2018
 * @file hc-06.hpp
 */

#ifndef HC06_H
#define HC06_H

#include "bluetooth.hpp"
#include "wrap-hwlib.hpp"
#include <string>

class HC06 : public Bluetooth {
  private:
    uint8_t discoveredDevices[32]; /// Used for storing the connection id of a discovered device.
    std::string name;              /// Used for storing the name of this device.
    unsigned int currentBaudrate;

  public:
    HC06();

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
    std::string getName();

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
     * @brief Used to retrieve the message.
     *
     * Provide this function with own data buffer. The buffer will hold the received message.
     *
     * @param[in]     deviceID    An unique ID of a device.
     *
     */
    void receive(uint8_t *data);

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
    void setName(const std::string &newName);

    /**
     * @brief choose whether the chip will be discoverable or not.
     *
     * @param[in]     visible    An boolean to set the visibility.
     */
    void setVisibility(bool visible);
};

#endif
