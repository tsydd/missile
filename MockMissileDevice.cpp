//
// Created by Dmitry Tsydzik on 6.7.16.
//

#include "MockMissileDevice.h"

#include <cstdio>

void MockMissileDevice::moveDown() {
    printf("mock down\n");
}

void MockMissileDevice::moveUp() {
    printf("mock up\n");
}

void MockMissileDevice::moveLeft() {
    printf("mock left\n");
}

void MockMissileDevice::moveRight() {
    printf("mock right\n");
}

void MockMissileDevice::stop() {
    printf("mock stop\n");
}

void MockMissileDevice::fire() {
    printf("mock fire\n");
}

void MockMissileDevice::stopFire() {
    printf("mock stop fire\n");
}
