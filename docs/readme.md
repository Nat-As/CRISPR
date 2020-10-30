# Documentation
1. [LCD Display](https://github.com/Nat-As/CRISPR/blob/main/docs/OSEPP.pdf)
# Circuit Build
The LCD pinout is described below:
<br>
![img](/src/lcd.png)

The LCD is connected to an Arduino UNO in this scenario. PORTD (Pins 0-7) are used to send an entire byte to the LCD module. Pins 0-7 on the Arduino will directly map to Pins DB0-7 on the LCD display according to it's documantation ([attached](https://github.com/Nat-As/CRISPR/blob/main/docs/OSEPP.pdf)).
