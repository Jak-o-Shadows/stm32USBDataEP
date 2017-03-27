#ifndef USBSIDE
#define USBSIDE

#include <stdlib.h>
#include <stdbool.h>

//#include <unicore-mx/cm3/nvic.h>
//#include <unicore-mx/cm3/systick.h>
//#include <unicore-mx/usbd/usbd.h>
//#include <unicore-mx/usbd/misc/string.h>

#include <libopencm3/cm3/nvic.h>
#include <libopencm3/cm3/systick.h>
#include <libopencm3/usb/usbd.h>
//#include <libopencm3/usbd/misc/string.h>



#include "usbhid-target.h"

extern uint8_t started;

static usbd_device *usbd_dev;

//unicore-mx
//int usb_strings(usbd_device *dev, struct usbd_get_string_arg *arg);

//unicore-mx
//int hid_control_request(usbd_device *dev, struct usbd_control_arg *arg);


//unicore-mx
//void hid_set_config(usbd_device *dev, const struct usb_config_descriptor *cfg);
//loc3
void hid_set_config(usbd_device *dev, uint16_t wValue);



void usbSetup(void);

void usbInLoop(void);

















#endif
