/*
 * MissileController.cpp
 *
 *  Created on: Jun 16, 2015
 *      Author: Dmitry Tsydzik
 */

#include "MissileController.h"

// Use initializer lists:
// MissleController::MissleController(arg1, arg2)
//    : member1(arg1)
//    , member2(arg2)
// {
//   // Non-trival initialization code
// }
MissileController::MissileController(Glib::RefPtr<Gtk::Application> *app,
                                     MissileKeyboardHandler *handler,
                                     MissileDevice *device) {
    this->m_pApp = app;
    this->m_pKbHandler = handler;
    this->m_pDevice = device;

    // I think it's better to add these in pairs so that each key's
    // press/release events are clearly handled.
    // Step 2 may be actually combining then in a single
    // function with a boolean argument.
    //
    // If you change the handler API per my other comments,
    // you can replace most of these with a lookup table & a single handler combo.
    // static std::unordered_map<uint32_t, device_command> commands = {
    //   GDK_KEY_w, device_command::move_left,
    //   // ...
    // };
    // handler->set([&](uint32_t key_code) {
    //   auto iter = commands.find(key_code);
    //   if (iter != commands.end()) {
    //     log(key_code);
    //     m_pDevice->sendCommand(iter->second);
    //   }
    // });
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

// No need to define empty destructor - the compiler can do it for you.
// Or you could've provided it in the header file to make linker's
// and optimizer's jobs easier.
MissileController::~MissileController() {
}

int MissileController::run() {
    return m_pKbHandler->run(*m_pApp);
}

