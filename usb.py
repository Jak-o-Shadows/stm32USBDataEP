import usb

dev = usb.core.find(idVendor=0x0483, idProduct=0x5710)

dev.set_configuration()

print dev.read(0x81, 64, 100)


