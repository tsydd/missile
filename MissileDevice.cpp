/*
 * MissileDevice.cpp
 *
 *  Created on: Jun 4, 2015
 *      Author: Dmitry Tsydzik
 */

#include "MissileDevice.h"

#include "usb_utils.h"
// Use cstdtio and std::printf since we're in C++ land.
#include <stdio.h>

// Constant defines are evil.
// Use static type_t const var = value;
#define ID_VENDOR   0x0a81
#define ID_PRODUCT  0x0701

#define ML_CMD_REQUEST_TYPE 0x21
#define ML_CMD_REQUEST      0x09
#define ML_CMD_VALUE        0x00
#define ML_CMD_SIZE         8
#define ML_CMD_TIMEOUT      1000

#define ML_CTRL_DOWN        0b00000001
#define ML_CTRL_UP          0b00000010
#define ML_CTRL_LEFT        0b00000100
#define ML_CTRL_RIGHT       0b00001000
#define ML_CTRL_FIRE        0b00010000
#define ML_CTRL_STOP        0b00100000
#define ML_CTRL_STOP_FIRE   0b01000000

MissileDevice::MissileDevice() {
    // No need to say "struct" in C++, it's inferred by default
    // (unless you're deep inside some heavily templated code).
    struct usb_device *pDev = usb_find_device(ID_VENDOR, ID_PRODUCT);
    int interface = pDev->config->interface->altsetting->bInterfaceNumber;
    m_pDevHandle = usb_open(pDev);
    usb_claim(m_pDevHandle, interface);
    // Error handling?
}

MissileDevice::~MissileDevice() {
    usb_release_interface(m_pDevHandle, m_iface);
    usb_close(m_pDevHandle);
}

// Looks like a perfect use for some sort of
// map<direction_t, cmd_t> mapping.
// So you only have one action method that has the lookup table
// and does error control, dispatch, etc.
// E.g.:
// enum struct direction // C++11 typed enum
// {
//    UP,
//    DOWN,
//    LEFT,
//    RIGHT,
// };
//
// enum struct device_command
// {
//    REQUEST_TYPE = 0x21,
//    // ...
// };
//
// void move(direction dir)
// {
//   // Can be a static array for quick lookup speed.
//   static std::unordered_map<direction, device_cmd> commands = {
//     {direction::UP, device_command::CTRL_UP},
//     // ...
//   };
//
//   auto iter = commands.find(dir);
//   if (iter == commands.end()){
//     // log(Unknown command)
//   } else {
//     sendCmd(iter->second);
//   }
// }
void MissileDevice::moveDown()
{
    sendCmd(ML_CTRL_DOWN);
}

void MissileDevice::moveUp()
{
    sendCmd(ML_CTRL_UP);
}

void MissileDevice::moveLeft()
{
    sendCmd(ML_CTRL_LEFT);
}

void MissileDevice::moveRight()
{
    sendCmd(ML_CTRL_RIGHT);
}

void MissileDevice::stop() {
    sendCmd(ML_CTRL_STOP);
}

void MissileDevice::fire()
{
    sendCmd(ML_CTRL_FIRE);
}

void MissileDevice::stopFire() {
    sendCmd(ML_CTRL_STOP_FIRE);
}

// char is a poor type choice here as it usually implies ASCII, doesn't it?
// I'd rather change to uint8_t - or, as pointed out above - to a typed enum.
void MissileDevice::sendCmd(char cmd) {
    int ret = usb_control_msg(m_pDevHandle,
                              ML_CMD_REQUEST_TYPE,
                              ML_CMD_REQUEST,
                              ML_CMD_VALUE,
                              0,
                              // Memory leak on each command?
                              // this buffer has to be freed by someone.
                              new char[ML_CMD_SIZE]{cmd},
                              ML_CMD_SIZE,
                              ML_CMD_TIMEOUT);
    if (ret < 0) {
        // Print the command and error code as well?
        printf("Failed to send command to missile\n");
    }
}
