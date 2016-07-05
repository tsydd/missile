/*
 * MissileController.cpp
 *
 *  Created on: Jun 16, 2015
 *      Author: Dmitry Tsydzik
 */

#include "MissileController.h"

MissileController::MissileController(Glib::RefPtr<Gtk::Application> *app,
                                     MissileKeyboardHandler *handler,
                                     MissileDevice *device)
        : m_pApp(app)
        , m_pKbHandler(handler)
        , m_pDevice(device)
{

    handler->addKeyPressedHandler(GDK_KEY_w, [&]() {
        printf("up\n");
        this->m_pDevice->moveUp();
    });
    handler->addKeyPressedHandler(GDK_KEY_a, [&]() {
        printf("left\n");
        this->m_pDevice->moveLeft();
    });
    handler->addKeyPressedHandler(GDK_KEY_s, [&]() {
        printf("down\n");
        this->m_pDevice->moveDown();
    });
    handler->addKeyPressedHandler(GDK_KEY_d, [&]() {
        printf("right\n");
        this->m_pDevice->moveRight();
    });
    handler->addKeyPressedHandler(GDK_KEY_space, [&]() {
        printf("fire\n");
        this->m_pDevice->fire();
    });

    handler->addKeyReleasedHandler(GDK_KEY_w, [&]() {
        printf("up released\n");
        this->m_pDevice->stop();
    });
    handler->addKeyReleasedHandler(GDK_KEY_a, [&]() {
        printf("left released\n");
        this->m_pDevice->stop();
    });
    handler->addKeyReleasedHandler(GDK_KEY_s, [&]() {
        printf("down released\n");
        this->m_pDevice->stop();
    });
    handler->addKeyReleasedHandler(GDK_KEY_d, [&]() {
        printf("right released\n");
        this->m_pDevice->stop();
    });
    handler->addKeyReleasedHandler(GDK_KEY_space, [&]() {
        printf("fire released\n");
        this->m_pDevice->stopFire();
    });
}

int MissileController::run() {
    return m_pKbHandler->run(*m_pApp);
}

