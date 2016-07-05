//
// Created by tsyd on 24.6.16.
//

#include <cstdio>
#include <stdexcept>

#include "usb_utils.h"

struct usb_device *usb_find_device(uint16_t idVendor, uint16_t idProduct) {
    usb_init();
    usb_find_busses();
    usb_find_devices();

    for (auto bus = usb_get_busses(); bus; bus = bus->next) {
        for (auto dev = bus->devices; dev; dev = dev->next) {
            auto dscr = &dev->descriptor;
            if (idVendor == dscr->idVendor && idProduct == dscr->idProduct) {
                printf("Device found\n");
                return dev;
            }
        }
    }
    throw std::runtime_error("Device not found");
}

void usb_claim(usb_dev_handle *handle, int iface) {
    char driverName[32];
    int ret = usb_get_driver_np(handle, iface, driverName, 31);
    if (ret == 0) {
        printf("Claimed by driver %d: %s\n", iface, driverName);
        int detached = usb_detach_kernel_driver_np(handle, iface);
        if (detached == 0) {
            printf("Device detached\n");
        }
        else {
            throw std::runtime_error("Failed to detach");
        }
    } else{
        printf("Warning: device detach step is skipped\n");
    }

    int claimed = usb_claim_interface(handle, iface);
    if (claimed == 0) {
        printf("Successfully claimed\n");
    }
    else {
        throw std::runtime_error("Failed to claim. Ensure user is root");
    }
}
