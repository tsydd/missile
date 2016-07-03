/*
 * MissileKeyboardHandler.cpp
 *
 *  Created on: Jun 14, 2015
 *      Author: Dmitry Tsydzik
 */

#include "MissileKeyboardHandler.h"

MissileKeyboardHandler::MissileKeyboardHandler() {
    // Shame this thing doesn't accept lambdas... or does it?
    window.signal_key_press_event().connect(sigc::mem_fun(this, &MissileKeyboardHandler::onKeyPressed), false);
    window.signal_key_release_event().connect(sigc::mem_fun(this, &MissileKeyboardHandler::onKeyReleased));
}

MissileKeyboardHandler::~MissileKeyboardHandler() {
}

int MissileKeyboardHandler::run(Glib::RefPtr<Gtk::Application> app) {
    return app->run(window);
}

bool MissileKeyboardHandler::onKeyPressed(GdkEventKey *key) {
    guint keyval = key->keyval;
    if (m_lastKey == keyval && !m_releaseHandled) {
        return true;
    }
    // This:
    // a) Modifies the map if handler doesn't exist => extra allocations
    // b) Always copies the handler
    //    (so if it captured some large vector by value,
    //    you'll copy it on every single lookup).
    //
    // Here's how to fix both:
    // auto iter = m_keyPressedHandlers.find(keyval);
    // if (iter == m_keyPressedHandlers.end()) {
    //   return false;
    // }
    //   m_releaseHandled = false;
    //   m_lastKey = keyval;
    //   (iter->second)();
    //   return true;
    // }
    std::function<void()> handler = m_keyPressedHandlers[keyval];
    if (handler != NULL) {
        // Shouldn't each key have its own such flag?
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
    // Same as above, too many extra allocations
    std::function<void()> handler = m_keyReleasedHandlers[key->keyval];
    // Checking for null works, but is a poor way to do this.
    // Just test like this: 'if (handler) { ... }'
    if (handler != NULL) {
        m_releaseHandled = true;
        handler();
    }
    // Shouldn't this return false sicne the key release event hasn't been consumed?
    return true;
}

void MissileKeyboardHandler::addKeyPressedHandler(guint key, std::function<void()> handler) {
    // this function creates 2 extra copies of the callback: one when passing the argument
    // (unless you give an rvalue which std::function's constructor will move from, thus eliminating one copy)
    // and another one when inserting here.
    // 1) Mark your intent to take ownership of the handler callback in the function signature:
    //   std::function<void()> && handler)
    // 2) Move from it when adding to the map:
    //   m_keyPressedHandlers[key] = std::move(handler).
    // That way, your code never creates copies on its own.
    m_keyPressedHandlers[key] = handler;
}

void MissileKeyboardHandler::addKeyReleasedHandler(guint key, std::function<void()> handler) {
    m_keyReleasedHandlers[key] = handler;
}
