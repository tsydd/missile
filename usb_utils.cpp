//
// Created by tsyd on 24.6.16.
//

// #include <cstdio>
#include <stdio.h>
#include <stdexcept>

#include "usb_utils.h"

struct usb_device *usb_find_device(uint16_t idVendor, uint16_t idProduct) {
    // No error checks / early bailout?
    usb_init();
    usb_find_busses();
    usb_find_devices();

    // Please omit the "struct" keyword.
    // Moreover, this part looks like a perfect use for the auto type specifier.
    // for (auto * dev = bus->devices; dev; dev = dev->next)
    for (struct usb_bus *bus = usb_get_busses(); bus; bus = bus->next) {
        for (struct usb_device *dev = bus->devices; dev; dev = dev->next) {
            struct usb_device_descriptor *dscr = &dev->descriptor;
            if (idVendor == dscr->idVendor && idProduct == dscr->idProduct) {
                // Print the device info just in case?
                printf("Device found\n");
                return dev;
            }
        }
    }
    // The rest of your APIs don't use execptions, why throw
    // if nobody ever catches them?
    throw std::runtime_error("Device not found");
}

// It appears that we can reorganize your code in a cleaner way,
// checking for errors first.
// char driverName[32];
// int ret = usb_get_driver_np(handle, iface, driverName, 31);
// if (ret != 0) {
//    log(Device detach skipped);
// } else {
//    log(device claimed by driver...);
//    int detached = usb_detach_kernel_driver_np(...);
//    if (detached != 0) {
//       return ERR_FAILED_TO_DETACH;
//    }
//
//    log(Device detached successfully);
// }
//
// int claimed = usb_claim_interface(...);
// if (claimed != 0) {
//    return ERR_FAILED_TO_CLAIM_DEVICE;
// }
//
// log(Successfully claimed the device);
//
// Such flow is especially efficient when paired with RAII-style holders,
// but makes it easier to follow the code regardless.
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
