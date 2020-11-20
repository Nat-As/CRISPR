# CRISPR
An affordable CRISPR with an Arduino AT328P. This system demonstrates affordable gene splicing technology for DNA modification using the CRISPR CAS9 and CAS13 systems. This is an experimental project which serves as a proof of concept design to aid in future bio-engineering efforts.

# Components
There are three main components to this system:
+ The Microcontroller
+ The Interface
+ The High Voltage Driver

<br>
This repository is used to program the Microcontroller (an ATmel AT328P) by flashing the hex file with avrdude v6.3 or higher. The controller will connect to the interface and also controll the high voltage driver circuit by sending 2kV to the organism. This high voltage pulse will cause a phenomena known as electroporation, where the cell membrane is made to be porous so that it can accept the transfection of new DNA.

# Build
The arduino UNO will be connected to the LCD as shown below.
|LCD|Arduino|
|---|-------|
|VSS|GND    |
|VDD|+5V|
|V0|GND POT|
|RS|9|
|RW|GND|
|E|8|
|D0|7|
|D1|6|
|D2|5|
|D3|4|
|D4|3|
|D5|2|
|D6|1|
|D7|0|
|A|+5V|
|K|GND|

# Compile
You can use atmel studio with it's included libraries, or build the project on linux with the included build scripts:
1. ```/bin/avr-compile```
2. ```/bin/avr-flash```
3. Step 2 will ask for sudo password to access serial devices.
