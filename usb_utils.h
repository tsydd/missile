//
// Created by tsyd on 24.6.16.
// Header message mismatch detected :)
//

#ifndef MISSILE_USB_UTILS_H
#define MISSILE_USB_UTILS_H

// Even though we don't have to include this (liek I suggested in other headers),
// here it's 100% justified as any used of these methoes will likely want to do
// something extra with the usb-related structs so it's good that we take responsibility
// fo providing the definition.
#include <usb.h>

// No need for the "struct" part.
struct usb_device *usb_find_device(uint16_t idVendor, uint16_t idProduct);

void usb_claim(usb_dev_handle *handle, int iface);

#endif //MISSILE_USB_UTILS_H
