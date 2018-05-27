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

#include "wrap-hwlib.hpp"
#include "bluetooth.hpp"

/// \brief
/// HC-06 bluetooth library
class HC06 : public bluetooth{
private:
    uint8_t name[32]; /// Used for storing the name of this device.
    uint8_t discoveredDevices[32]; /// Used for storing the connection id of a discovered device.
public:
    HC06();

    /// \brief
    /// Used to connect to other devices
    /// \details
    /// Connect to the specified device ID. To get the device ID use function "search".
    /// @param[in] device ID
    void connect(int deviceID);

    /// \brief
    /// Used to disconnect form a device.
    void disconnect();

    /// \brief
    /// Used to read the name of this device.
    /// @return current device name
    uint8_t* getName();

    /// \brief
    /// Used to read the status of the HC-06 chip.
    /// @return Int of current status
    int getStatus();

    /// \brief
    /// Used to pair with other devices.
    /// \details
    /// Pair with the specified device ID. To get the device ID use function "search".
    /// @param[in] device ID

    void pair(int deviceID);
    
    /// \brief
    /// Used to retrieve the message.
    /// \details
    /// Provide this function with own data buffer. The buffer will hold the received message.
    /// @param[in] Data
    void receive(uint8_t *data);

    /// \brief
    /// Used to discover any discoverable devices.
    /// \details
    /// This function will return a device id for all discovered devices. Use this ID to connect.
    /// @return discovered device IDs
    uint8_t* search();

    /// \brief
    /// Used to send data to other devices.
    /// \details
    /// This function will send the data provided.
    /// @param[in] Data
    void send(uint8_t *data);

    /// \brief
    /// Used to set the baud rate of the connection.
    /// @param[in] baud rate
    void setBaud(int baud);

    /// \brief
    /// Used to set the name of the chip. This is not an ID
    /// @param[in] name of the bluetooth module
    void setName(const uint8_t *name);

    /// \brief
    /// choose whether the chip will be discoverable or not.
    /// @param[in] bool true or false
    void setVisibility(bool visible);

};

#endif
