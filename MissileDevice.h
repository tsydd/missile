/*
 * MissileDevice.h
 *
 *  Created on: Jun 4, 2015 // 2016? :)
 *      Author: Dmitry Tsydzik
 */

// Include guards are inferior to #pragma once.
// The compiler can be more certain about the intent of #pragma once
// and there's no collision possibility (if working with a multi-library project).
#ifndef MISSILE_DEVICE_H
#define MISSILE_DEVICE_H

// No need to require users of your header to depend on usb.
// Strictly speaking, only the .cpp file needs it since you only have a ponter member.
// Just forward-declare:
// struct usb_dev_handle;
// This will absolve you from needint to include usb.h in this file.
#include <usb.h>

class MissileDevice {
public:
    MissileDevice();
    // Why is it virtual? Does anybody inherit from this class?
    // If so, most of the action methods ought to be vrtual as well.
    virtual ~MissileDevice();

    void moveDown();
    void moveUp();
    void moveLeft();
    void moveRight();

    // What does stop() do? Stop moving, stop shooting, somethign else?
    void stop();

    // Call it startFire() for consistency?
    void fire();

    void stopFire();

    // Should this be a private method?
    void sendCmd(char cmd);

private:
    usb_dev_handle *m_pDevHandle;
    int m_iface;
};


#endif //MISSILE_DEVICE_H
