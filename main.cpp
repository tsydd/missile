#include "MissileDevice.h"
#include "MockMissileDevice.h"
#include "MissileKeyboardHandler.h"
#include "MissileController.h"

int main(int argc, char **argv) {
    auto app = Gtk::Application::create(argc, argv, "by.tsyd.missile");
    Gtk::Window window;

    MissileDevice device;
//    MockMissileDevice device;

    MissileKeyboardHandler handler(window);
    MissileController controller(app, handler, device);

    return controller.run();
}