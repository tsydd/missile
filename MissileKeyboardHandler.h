/*
 * MissileKeyboardHandler.h
 *
 *  Created on: Jun 14, 2015
 *      Author: Dmitry Tsydzik
 */

#pragma once

#include <gtkmm.h>
#include <map>

class MissileKeyboardHandler {
public:
    MissileKeyboardHandler(Gtk::Window &window);

    int run(Glib::RefPtr<Gtk::Application> app);

    void addKeyPressedHandler(guint key, std::function<void()> &&handler);

    void addKeyReleasedHandler(guint key, std::function<void()> &&handler);

private:
    Gtk::Window &m_window;

    bool onKeyPressed(GdkEventKey *key);

    bool onKeyReleased(GdkEventKey *key);

    std::map<guint, std::function<void()>> m_keyPressedHandlers;
    std::map<guint, std::function<void()>> m_keyReleasedHandlers;
    guint m_lastKey = 0;
    bool m_releaseHandled = true;
};
