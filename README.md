# CRISPR
An affordable CRISPR with an Arduino AT328P. This system demonstrates affordable gene splicing technology for DNA modification using the CRISPR CAS9 and CAS13 systems. This is an experimental project which serves as a proof of concept design.

# Components
There are three main components to this system:
+ The Microcontroller
+ The Interface
+ The High Voltage Driver

<br>
This repository is used to program the Microcontroller (an ATmel AT328P) by flashing the hex file with avrdude v6.3 or higher. The controller will connect to the interface and also controll the high voltage driver circuit by sending 2kV to the organism. This high voltage pulse will cause a phenomena known as electroporation, where the cell membrane is made to be porous so that it can accept the transfection of new DNA.
