/*
 * This file is part of the unicore-mx project.
 *
 * Copyright (C) 2010 Gareth McMullin <gareth@blacksphere.co.nz>
 * Copyright (C) 2011 Piotr Esden-Tempski <piotr@esden.net>
 * Copyright (C) 2015 Kuldeep Singh Dhaka <kuldeepdhaka9@gmail.com>
 *
 * This library is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this library.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <stdlib.h>
#include <stdbool.h>
#include <unicore-mx/stm32/rcc.h>


#include <unicore-mx/cm3/nvic.h>
#include <unicore-mx/cm3/systick.h>
#include <unicore-mx/usbd/usbd.h>
#include <unicore-mx/usb/class/hid.h>
#include <unicore-mx/usbd/misc/string.h>
#include "lowlevel/usbhid-target.h"
#include "lowlevel/usb.h"



int main(void) {
	
	usbSetup();


	usbhid_target_usbd_after_init_and_before_first_poll();
	
	while (1) {
		__asm__("nop");
		//usbInLoop();// same as usbd_poll(usbd_dev);
	}
}



void sys_tick_handler(void)
{
	//uint8_t buf[9];
	
	//pollSensors(buf, 9);
	//testOutputs(buf, 9);

	//writeToEndpoint(0x81, buf, sizeof(buf));
}
