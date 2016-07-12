//
// Created by Dmitry Tsydzik on 6.7.16.
//

#pragma once

#include "IMissileDevice.h"

class MockMissileDevice : public IMissileDevice {
    void moveDown() override;

    void moveUp() override;

    void moveLeft() override;

    void moveRight() override;

    void stop() override;

    void fire() override;

    void stopFire() override;
};
