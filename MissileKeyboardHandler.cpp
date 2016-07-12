/*
 * MissileKeyboardHandler.cpp
 *
 *  Created on: Jun 14, 2015
 *      Author: Dmitry Tsydzik
 */

#include "MissileKeyboardHandler.h"

MissileKeyboardHandler::MissileKeyboardHandler(Gtk::Window &window) : m_window(window) {
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
    auto iter = m_keyPressedHandlers.find(keyval);
    if (iter == m_keyPressedHandlers.end()) {
        return false;
    }
    m_releaseHandled = false;
    m_lastKey = keyval;
    (iter->second)();
    return true;
}

bool MissileKeyboardHandler::onKeyReleased(GdkEventKey *key) {
    guint keyval = key->keyval;
    if (m_lastKey != keyval) {
        return false;
    }
    auto iter = m_keyReleasedHandlers.find(key->keyval);
    if (iter == m_keyReleasedHandlers.end()) {
        return false;
    }
    m_releaseHandled = true;
    (iter->second)();
    return true;
}

void MissileKeyboardHandler::addKeyPressedHandler(guint key, std::function<void()> &&handler) {
    m_keyPressedHandlers[key] = std::move(handler);
}

void MissileKeyboardHandler::addKeyReleasedHandler(guint key, std::function<void()> &&handler) {
    m_keyReleasedHandlers[key] = std::move(handler);
}
