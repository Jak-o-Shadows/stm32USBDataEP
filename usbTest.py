
import time


import usb




dev = usb.core.find(idVendor=0x0483, idProduct=0x5710)

dev.set_configuration()
a = time.time()
for i in xrange(1024*1024*2/64):
	d = dev.read(0x81, 64, 100)
b = time.time()
print b-a

a = time.time()
for i in xrange(1024*1024*2/64):
	dev.write(0x01, d, 100)
b = time.time()
print b-a
