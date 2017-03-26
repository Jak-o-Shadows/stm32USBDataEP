#ifndef USBSIDE
#define USBSIDE

#include <stdlib.h>
#include <stdbool.h>

#include <unicore-mx/cm3/nvic.h>
#include <unicore-mx/cm3/systick.h>
#include <unicore-mx/usbd/usbd.h>
#include <unicore-mx/usb/class/hid.h>
#include <unicore-mx/usbd/misc/string.h>
#include "usbhid-target.h"

extern uint8_t started;

static usbd_device *usbd_dev;


int usb_strings(usbd_device *dev, struct usbd_get_string_arg *arg);

int hid_control_request(usbd_device *dev, struct usbd_control_arg *arg);

void hid_set_config(usbd_device *dev,
				const struct usb_config_descriptor *cfg);



void usbSetup(void);

void usbInLoop(void);

















#endif
