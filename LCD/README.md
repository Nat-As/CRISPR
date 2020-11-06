# Documentation

![LCD](/src/lcd.png)

The LCD pins DB0 - DB7 are connected to the Arduino pins 0-7 (PORTD) respectively. The Arduino A0 and A1 pins are reserved for the RS and RW pins on the LCD respectively. The LCD pin V0 is connected to a grounded variable resistor which changes the contrast of the display. LCD pins 1, 16 are connected to ground. LCD pins 2, 15 are connected to a +5V source to power the LCD. This source can come from the arduino 5V pins.
