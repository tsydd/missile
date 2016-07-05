//
// Created by tsyd on 24.6.16.
//

#pragma once

#include <usb.h>

struct usb_device *usb_find_device(uint16_t idVendor, uint16_t idProduct);

void usb_claim(usb_dev_handle *handle, int iface);
