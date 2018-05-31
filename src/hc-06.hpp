// ==========================================================================
//
// File      : hc-06.hpp
// Part of   : C++ library for using the hc-06 bluetooth module.
//
// ==========================================================================

// this file contains Doxygen lines
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

/// \brief
/// HC-06 bluetooth library
class HC06 : public Bluetooth {
  private:
    uint8_t name[32];              /// Used for storing the name of this device.
    uint8_t discoveredDevices[32]; /// Used for storing the connection id of a discovered device.
  public:
    HC06();

    /**
     * @brief Used to connect to other devices.
     * [BLANK]
     * Connect to the specified device ID. To get the device ID use function "search".
     * [BLANK]
     * @param[in]     deviceID    An unique ID of a device.
     * @return void
     */
    void connect(int deviceID);

    /**
     * @brief Used to disconnect from other devices.
     * @return void
     */
    void disconnect();

    /**
     * @brief Used to read the name of this device.
     * [BLANK]
     * This function will read the current device name and return an array with characters.
     * [BLANK]
     * @return uint8_t array with the name.
     */
    uint8_t *getName();

    /**
     * @brief Used to read the status of the HC-06 chip.
     * [BLANK]
     * This function will check if the chip is detected and functional by performing a simple communication test.
     * [BLANK]
     * @return Int of current status.
     */
    int getStatus();

    /**
     * @brief Used to pair with other devices.
     * [BLANK]
     * Pair with the specified device ID. To get the device ID use function "search".
     * [BLANK]
     * @param[in]     deviceID    An unique ID of a device.
     * @return void
     */
    void pair(int deviceID);

    /**
     * @brief Used to retrieve the message.
     * [BLANK]
     * Provide this function with own data buffer. The buffer will hold the received message.
     * [BLANK]
     * @param[in]     deviceID    An unique ID of a device.
     * @return void
     */
    void receive(uint8_t *data);

    /**
     * @brief Used to discover any discoverable devices.
     * [BLANK]
     * This function will return a device id for all discovered devices. Use this ID to connect.
     * [BLANK]
     * @return uint8_t pointer to an array of unique device ID's.
     */
    uint8_t *search();

    /**
     * @brief Used to send data to other devices.
     * [BLANK]
     * This function will send the data provided.
     * [BLANK]
     * @param[in]     data    A pointer to a uint8_t data array.
     * @return void
     */
    void send(uint8_t *data);

    /**
     * @brief Used to set the baud rate of the connection.
     * @param[in]     baud    An integer specifying the baud rate.
     * @return void
     */
    void setBaud(int baud);

    /**
     * @brief Used to set the name of the chip. This is not an ID
     * @param[in]     name    A pointer to an uint8_t data array holding the name.
     * @return void
     */
    void setName(const uint8_t *name);

    /**
     * @brief choose whether the chip will be discoverable or not.
     * @param[in]     visible    An boolean to set the visibility.
     * @return void
     */
    void setVisibility(bool visible);
};

#endif
