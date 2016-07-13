//
// Created by Dmitry Tsydzik on 24.6.16.
//

#pragma once

struct usb_dev_handle;

struct usb_device *usb_find_device(unsigned short idVendor, unsigned short idProduct);

void usb_claim(usb_dev_handle *handle, int iface);
