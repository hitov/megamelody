#avrdude -c jtag1 -p m162 -P /dev/ttyUSB0 -e
#avrdude -c jtag1 -p m162 -P /dev/ttyUSB0 -U lfuse:w:0xff:m -U hfuse:w:0x99:m
#avrdude -c jtagmkI -p m162 -P /dev/ttyUSB0 -U hfuse:w:0x99:m -U efuse:w:0xff:m 
avrdude -b 38400 -c avr910 -p m8 -P /dev/ttyUSB0 -U lfuse:w:0x3f:m -U hfuse:w:0xd9:m 
#avrdude -c jtag1 -p m162 -P /dev/ttyUSB0 -U flash:w:megamelody.hex
#make clean
#make
#make install
