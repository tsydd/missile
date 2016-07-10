/*
 * MissileKeyboardHandler.cpp
 *
 *  Created on: Jun 14, 2015
 *      Author: Dmitry Tsydzik
 */

#include "MissileKeyboardHandler.h"

MissileKeyboardHandler::MissileKeyboardHandler(Gtk::Window &window): m_window(window) {
    m_window.signal_key_press_event().connect(sigc::mem_fun(this, &MissileKeyboardHandler::onKeyPressed), false);
    m_window.signal_key_release_event().connect(sigc::mem_fun(this, &MissileKeyboardHandler::onKeyReleased));
}

int MissileKeyboardHandler::run(Glib::RefPtr<Gtk::Application> app) {
    return app->run(m_window);
}

bool MissileKeyboardHandler::onKeyPressed(GdkEventKey *key) {
    guint keyval = key->keyval;
    if (m_lastKey == keyval && !m_releaseHandled) {
        return true;
    }
    std::function<void()> handler = m_keyPressedHandlers[keyval];
    if (handler != NULL) {
        m_releaseHandled = false;
        m_lastKey = keyval;
        handler();
    }
    return true;
}

bool MissileKeyboardHandler::onKeyReleased(GdkEventKey *key) {
    guint keyval = key->keyval;
    if (m_lastKey != keyval) {
        return false;
    }
    std::function<void()> handler = m_keyReleasedHandlers[key->keyval];
    if (handler != NULL) {
        m_releaseHandled = true;
        handler();
    }
    return true;
}

void MissileKeyboardHandler::addKeyPressedHandler(guint key, std::function<void()> handler) {
    m_keyPressedHandlers[key] = handler;
}

void MissileKeyboardHandler::addKeyReleasedHandler(guint key, std::function<void()> handler) {
    m_keyReleasedHandlers[key] = handler;
}
