#ifndef BLUETOOTH_H
#define BLUETOOTH_H

#include "wrap-hwlib.hpp"

class bluetooth {
  public:
    /// \brief
    /// Used to connect to other devices
    /// \details
    /// Connect to the specified device ID. To get the device ID use function "search".
    virtual void connect(int deviceID) = 0;

    /// \brief
    /// Used to disconnect form a device.
    virtual void disconnect() = 0;

    /// \brief
    /// Used to read the name of this device.
    virtual uint8_t *getName() = 0;

    /// \brief
    /// Used to read the status of the HC-06 chip.
    virtual int getStatus() = 0;

    /// \brief
    /// Used to pair with other devices.
    /// \details
    /// Pair with the specified device ID. To get the device ID use function "search".
    virtual void pair(int deviceID) = 0;

    /// \brief
    /// Used to retrieve the message.
    /// \details
    /// Provide this function with own data buffer. The buffer will hold the received message.
    virtual void receive(uint8_t *data) = 0;

    /// \brief
    /// Used to discover any discoverable devices.
    /// \details
    /// This function will return a device id for all discovered devices. Use this ID to connect.
    virtual uint8_t *search() = 0;

    /// \brief
    /// Used to send data to other devices.
    /// \details
    /// This function will send the data provided.
    virtual void send(uint8_t *data) = 0;

    /// \brief
    /// Used to set the baud rate of the connection.
    virtual void setBaud(int baud) = 0;

    /// \brief
    /// Used to set the name of the chip.
    virtual void setName(const uint8_t *name) = 0;

    /// \brief
    /// choose whether the chip will be discoverable or not.
    virtual void setVisibility(bool visible) = 0;
};

#endif