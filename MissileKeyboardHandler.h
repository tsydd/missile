/*
 * MissileKeyboardHandler.h
 *
 *  Created on: Jun 14, 2015
 *      Author: Dmitry Tsydzik
 */

#ifndef MISSILE_KEYBOARD_HANDLER_H_
#define MISSILE_KEYBOARD_HANDLER_H_

#include <gtkmm.h>
#include <map>

class MissileKeyboardHandler {
private:
    Gtk::Window window;

    bool onKeyPressed(GdkEventKey *key);

    bool onKeyReleased(GdkEventKey *key);

    // unordered_map is probably better if you don't care about ordering.
    // It also has smaller memory footprint (no that it matters in this simple case, though).
    std::map<guint, std::function<void()>> m_keyPressedHandlers;
    std::map<guint, std::function<void()>> m_keyReleasedHandlers;
    guint m_lastKey = 0;
    bool m_releaseHandled = true;
public:
    MissileKeyboardHandler();

    virtual ~MissileKeyboardHandler() /* = default */;

    // Why can't it take a simple pointer/reference?
    int run(Glib::RefPtr<Gtk::Application> app);

    // This will always create a copy before even entering the method.
    // Be careful with extra allocations.
    void addKeyPressedHandler(guint key, std::function<void()> handler);

    // You really need to typedef the handler type to keep clean API:
    // using key_state_handler_t = std::function<void()>;
    void addKeyReleasedHandler(guint key, std::function<void()> handler);
};

#endif /* MISSILE_KEYBOARD_HANDLER_H_ */
