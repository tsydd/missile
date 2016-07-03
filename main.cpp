#include "MissileDevice.h"
#include "MissileKeyboardHandler.h"
#include "MissileController.h"

int main(int argc, char **argv) {
    // memory leak: use std::unique_ptr or simple stack allocation.
    // Don't new/delete objects yourself, it's considered bad code.
    MissileDevice *device = new MissileDevice();
    // Change the app name to something more relevant? :)
    Glib::RefPtr<Gtk::Application> app = Gtk::Application::create(argc, argv, "grk.example.gtkmm.base");
    MissileKeyboardHandler *handler = new MissileKeyboardHandler();
    MissileController *controller = new MissileController(&app, handler, device);

    return controller->run();
}
