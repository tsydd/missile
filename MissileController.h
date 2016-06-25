/*
 * MissileController.h
 *
 *  Created on: Jun 16, 2015
 *      Author: Dmitry Tsydzik
 */

#ifndef MISSILE_CONTROLLER_H_
#define MISSILE_CONTROLLER_H_

#include <gtkmm.h>
#include <map>
#include "MissileKeyboardHandler.h"
#include "MissileDevice.h"

class MissileController {
private:
    Glib::RefPtr<Gtk::Application> *m_pApp;
    MissileKeyboardHandler *m_pKbHandler;
    MissileDevice *m_pDevice;
public:
    MissileController(Glib::RefPtr<Gtk::Application> *app,
                      MissileKeyboardHandler *handler,
                      MissileDevice *device);

    virtual ~MissileController();

    int run();
};

#endif /* MISSILE_CONTROLLER_H_ */
