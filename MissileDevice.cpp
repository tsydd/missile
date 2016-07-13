/*
 * MissileDevice.cpp
 *
 *  Created on: Jun 4, 2015
 *      Author: Dmitry Tsydzik
 */

#include "MissileDevice.h"

#include "usb_utils.h"
#include <cstdio>
#include <usb.h>
#include <bits/unique_ptr.h>

static const uint16_t ID_VENDOR = 0x0a81;
static const uint16_t ID_PRODUCT = 0x0701;

static const int ML_CMD_REQUEST_TYPE = 0x21;
static const int ML_CMD_REQUEST = 0x09;
static const int ML_CMD_VALUE = 0x00;
static const int ML_CMD_SIZE = 8;
static const int ML_CMD_TIMEOUT = 1000;

static const char ML_CTRL_DOWN = 0b00000001;
static const char ML_CTRL_UP = 0b00000010;
static const char ML_CTRL_LEFT = 0b00000100;
static const char ML_CTRL_RIGHT = 0b00001000;
static const char ML_CTRL_FIRE = 0b00010000;
static const char ML_CTRL_STOP = 0b00100000;
static const char ML_CTRL_STOP_FIRE = 0b01000000;

MissileDevice::MissileDevice() {
    struct usb_device *pDev = usb_find_device(ID_VENDOR, ID_PRODUCT);
    int interface = pDev->config->interface->altsetting->bInterfaceNumber;
    m_pDevHandle = usb_open(pDev);
    usb_claim(m_pDevHandle, interface);
}

MissileDevice::~MissileDevice() {
    usb_release_interface(m_pDevHandle, m_iface);
    usb_close(m_pDevHandle);
}

void MissileDevice::moveDown() {
    sendCmd(ML_CTRL_DOWN);
}

void MissileDevice::moveUp() {
    sendCmd(ML_CTRL_UP);
}

void MissileDevice::moveLeft() {
    sendCmd(ML_CTRL_LEFT);
}

void MissileDevice::moveRight() {
    sendCmd(ML_CTRL_RIGHT);
}

void MissileDevice::stop() {
    sendCmd(ML_CTRL_STOP);
}

void MissileDevice::fire() {
    sendCmd(ML_CTRL_FIRE);
}

void MissileDevice::stopFire() {
    sendCmd(ML_CTRL_STOP_FIRE);
}

void MissileDevice::sendCmd(char cmd) {
    std::unique_ptr<char[]> wrappedCmd(new char[ML_CMD_SIZE]{cmd});
    int ret = usb_control_msg(m_pDevHandle,
                              ML_CMD_REQUEST_TYPE,
                              ML_CMD_REQUEST,
                              ML_CMD_VALUE,
                              0,
                              wrappedCmd.get(),
                              ML_CMD_SIZE,
                              ML_CMD_TIMEOUT);
    if (ret < 0) {
        printf("Failed to send command to missile\n");
    }
}
