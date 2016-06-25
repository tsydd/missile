/*
 * MissileDevice.h
 *
 *  Created on: Jun 4, 2015
 *      Author: Dmitry Tsydzik
 */

#ifndef MISSILE_DEVICE_H
#define MISSILE_DEVICE_H

#include <usb.h>

class MissileDevice {
public:
    MissileDevice();
    virtual ~MissileDevice();

    void moveDown();
    void moveUp();
    void moveLeft();
    void moveRight();

    void stop();

    void fire();

    void stopFire();

    void sendCmd(char cmd);

private:
    usb_dev_handle *m_pDevHandle;
    int m_iface;
};


#endif //MISSILE_DEVICE_H
