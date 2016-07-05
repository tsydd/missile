/*
 * MissileController.h
 *
 *  Created on: Jun 16, 2015
 *      Author: Dmitry Tsydzik
 */

#pragma once

#include <gtkmm.h>
#include "MissileKeyboardHandler.h"
#include "MissileDevice.h"

class MissileController {
public:
    MissileController(Glib::RefPtr<Gtk::Application> *app,
                      MissileKeyboardHandler *handler,
                      MissileDevice *device);

    int run();

private:
    Glib::RefPtr<Gtk::Application> *m_pApp;
    MissileKeyboardHandler *m_pKbHandler;
    MissileDevice *m_pDevice;
};
