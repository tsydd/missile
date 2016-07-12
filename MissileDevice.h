/*
 * MissileDevice.h
 *
 *  Created on: Jun 4, 2015
 *      Author: Dmitry Tsydzik
 */

#pragma once

#include "IMissileDevice.h"

struct usb_dev_handle;

class MissileDevice : public IMissileDevice {
public:
    MissileDevice();

    ~MissileDevice();

    void moveDown() override;

    void moveUp() override;

    void moveLeft() override;

    void moveRight() override;

    void stop() override;

    void fire() override;

    void stopFire() override;

private:
    void sendCmd(char cmd);

    usb_dev_handle *m_pDevHandle;
    int m_iface;
};
