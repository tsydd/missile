//
// Created by tsyd on 24.6.16.
//

#ifndef MISSILE_USB_UTILS_H
#define MISSILE_USB_UTILS_H

#include <usb.h>

struct usb_device *usb_find_device(uint16_t idVendor, uint16_t idProduct);

void usb_claim(usb_dev_handle *handle, int iface);

#endif //MISSILE_USB_UTILS_H
