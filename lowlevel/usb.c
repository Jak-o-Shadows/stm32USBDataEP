/*
 * usb.c
 * 
 * Copyright 2017 jak <jak@linux-quu2>
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 * 
 * 
 */


#include "usb.h"


uint8_t usbd_control_buffer[128];

uint8_t started = 0;



const struct usb_endpoint_descriptor bulk_endpoint = {
	.bLength = USB_DT_ENDPOINT_SIZE,
	.bDescriptorType = USB_DT_ENDPOINT,
	.bEndpointAddress = 0x81,
	.bmAttributes = USB_ENDPOINT_ATTR_BULK,
	.wMaxPacketSize = 64,   //WAS 4 - CHANGED TO TEST SOMETHING ON THE 2-12-2016 BY J
	.bInterval = 1,
};

const struct usb_interface_descriptor bulk_iface = {
	.bLength = USB_DT_INTERFACE_SIZE,
	.bDescriptorType = USB_DT_INTERFACE,
	.bInterfaceNumber = 0,
	.bAlternateSetting = 0,
	.bNumEndpoints = 1,
	.bInterfaceClass = 0xFF, //FIX ME FIX ME - surely these have proper names?
	.bInterfaceSubClass = 0xFF, 
	.bInterfaceProtocol = 0xFF, 
	.iInterface = 0,

	.endpoint = &bulk_endpoint, //does this meant to have an &?

	.extra = NULL,//&hid_function,
	.extra_len = 0,//sizeof(hid_function),
};

const struct usb_interface ifaces[] = {{
	.num_altsetting = 1,
	.altsetting = &bulk_iface,
}};

const struct usb_config_descriptor config[] = {{
	.bLength = USB_DT_CONFIGURATION_SIZE,
	.bDescriptorType = USB_DT_CONFIGURATION,
	.wTotalLength = 0,
	.bNumInterfaces = 1,
	.bConfigurationValue = 1,
	.iConfiguration = 0,
	.bmAttributes = 0x80,
	.bMaxPower = 0x32,
	.interface = ifaces,
}};

const struct usb_device_descriptor dev_descr = {
	.bLength = USB_DT_DEVICE_SIZE,
	.bDescriptorType = USB_DT_DEVICE,
	.bcdUSB = 0x0200,
	.bDeviceClass = 0xFF,
	.bDeviceSubClass = 0,
	.bDeviceProtocol = 0,
	.bMaxPacketSize0 = 64,
	.idVendor = 0x0483,
	.idProduct = 0x5710,
	.bcdDevice = 0x0110,
	.iManufacturer = 1,
	.iProduct = 2,
	.iSerialNumber = 3,
	.bNumConfigurations = 1,

	.config = config
};

static const char *usb_strings_ascii[] = {
	"Black Sphere Technologies",
	"bulk",
	"none",
	"DEMO",
};





























int usb_strings(usbd_device *dev, struct usbd_get_string_arg *arg)
{
	(void)dev;
	return usbd_handle_string_ascii(arg, usb_strings_ascii, 4);
}

static void bulk_tx_cb(usbd_device *dev, uint8_t ep) {
	char buf[64] __attribute((aligned(4)));
	for (int i=1;i<64;i++){
		buf[i] = i;
	}
	
	(void)ep;
	
	//keep writing packets
	usbd_ep_write_packet(dev, 0x81, buf, 64);

}

void hid_set_config(usbd_device *dev,
				const struct usb_config_descriptor *cfg) {
					
	uint8_t data[64] __attribute__((aligned(4)));
	for (int i=1;i<64;i++){
		data[i] = i;
	}
					
					
	(void)cfg;

	usbd_ep_setup(dev, 0x81, USB_ENDPOINT_ATTR_BULK, 64, bulk_tx_cb); //last thing is a function!

	started = 1;
	
	usbd_ep_write_packet(dev, 0x81, data, 64);
	
}



void __attribute__((weak))
usbhid_target_usbd_after_init_and_before_first_poll(void) { /* empty */ }









































//USB is all tucked away now - therefore things like usbd_dev are not in
//the namespace of the main file. Therefore need some helper functins.


void usbSetup(void){
	usbhid_target_init(); //not HID specific. See usbhid-target.c

	usbd_dev = usbd_init(usbhid_target_usb_driver(), &dev_descr,
		usbd_control_buffer, sizeof(usbd_control_buffer)); //not HID specific. See usbhid-target.c


	usbd_register_set_config_callback(usbd_dev, hid_set_config); //not HID specific. See usbhid-target.c
	usbd_register_get_string_callback(usbd_dev, usb_strings);
	
	//enable interrupt
	nvic_enable_irq(NVIC_USB_LP_CAN_RX0_IRQ);
	nvic_enable_irq(NVIC_USB_WAKEUP_IRQ);
	
}

//POLLING FROM MAIN LOOP
void usbInLoop(void){
	usbd_poll(usbd_dev);
}


//various interrupts
void usb_wakeup_isr(void) {
  usbd_poll(usbd_dev);
}

void usb_lp_can_rx0_isr(void) {
  usbd_poll(usbd_dev);
}





