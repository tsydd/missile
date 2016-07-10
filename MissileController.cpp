/*
 * MissileController.cpp
 *
 *  Created on: Jun 16, 2015
 *      Author: Dmitry Tsydzik
 */

#include "MissileController.h"

MissileController::MissileController(Glib::RefPtr<Gtk::Application> app,
                                     MissileKeyboardHandler &handler,
                                     IMissileDevice &device)
        : m_app(app)
        , m_kbHandler(handler)
        , m_device(device)
{

    handler.addKeyPressedHandler(GDK_KEY_w, [&]() {
        printf("up\n");
        this->m_device.moveUp();
    });
    handler.addKeyPressedHandler(GDK_KEY_a, [&]() {
        printf("left\n");
        this->m_device.moveLeft();
    });
    handler.addKeyPressedHandler(GDK_KEY_s, [&]() {
        printf("down\n");
        this->m_device.moveDown();
    });
    handler.addKeyPressedHandler(GDK_KEY_d, [&]() {
        printf("right\n");
        this->m_device.moveRight();
    });
    handler.addKeyPressedHandler(GDK_KEY_space, [&]() {
        printf("fire\n");
        this->m_device.fire();
    });

    handler.addKeyReleasedHandler(GDK_KEY_w, [&]() {
        printf("up released\n");
        this->m_device.stop();
    });
    handler.addKeyReleasedHandler(GDK_KEY_a, [&]() {
        printf("left released\n");
        this->m_device.stop();
    });
    handler.addKeyReleasedHandler(GDK_KEY_s, [&]() {
        printf("down released\n");
        this->m_device.stop();
    });
    handler.addKeyReleasedHandler(GDK_KEY_d, [&]() {
        printf("right released\n");
        this->m_device.stop();
    });
    handler.addKeyReleasedHandler(GDK_KEY_space, [&]() {
        printf("fire released\n");
        this->m_device.stopFire();
    });
}

int MissileController::run() {
    return m_kbHandler.run(m_app);
}

