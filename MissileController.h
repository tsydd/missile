/*
 * MissileController.h
 *
 *  Created on: Jun 16, 2015
 *      Author: Dmitry Tsydzik
 */

// #pragma once FTW
#ifndef MISSILE_CONTROLLER_H_
#define MISSILE_CONTROLLER_H_

// Which of the headers are truly necessary here?
#include <gtkmm.h>
#include <map>
#include "MissileKeyboardHandler.h"
#include "MissileDevice.h"

// A slight inconsistency with other class declarations:
// some list data members at the top, some move them to the bottom.
// Let's use one style.
class MissileController {
private:
    // Why does this need a pointer to another smart pointer,
    // especially since MissleController doesn't own the object (or does it?)?
    // This is a perfect use for a simple reference (AKA a pointer that's never NULL).
    Glib::RefPtr<Gtk::Application> *m_pApp;
    MissileKeyboardHandler *m_pKbHandler;
    MissileDevice *m_pDevice;
public:
    MissileController(Glib::RefPtr<Gtk::Application> *app,
                      MissileKeyboardHandler *handler,
                      MissileDevice *device);

    // No need to be virtual
    virtual ~MissileController();

    int run();
};

#endif /* MISSILE_CONTROLLER_H_ */
