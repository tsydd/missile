#include "MissileDevice.h"
#include "MissileKeyboardHandler.h"
#include "MissileController.h"

int main(int argc, char **argv) {
    MissileDevice *device = new MissileDevice();
    Glib::RefPtr<Gtk::Application> app = Gtk::Application::create(argc, argv, "grk.example.gtkmm.base");
    MissileKeyboardHandler *handler = new MissileKeyboardHandler();
    MissileController *controller = new MissileController(&app, handler, device);

    return controller->run();
}