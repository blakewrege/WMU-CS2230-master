# Blink LED Tutorial 
[![Alt text](https://img.youtube.com/vi/nVEi3oidXM8/0.jpg)](https://www.youtube.com/watch?v=nVEi3oidXM8)(click image for video)  
Tutorial demonstrating how to blink an LED with an MSP430 as well as how to wire up an external LED to a breadboard. 
## Materials
- MSP430
- Breadboard
- 2 Jumper Wires
- 5mm Red LED

## Steps
- Insert the LED into the breadboard
- Connect a jumper cable to P1.0 and the breadboard in same row as the LED
- Connect the other jumper cable to GND and the breadboard in same row as the LED(next to the other)
- Create the blink executable `msp430-gcc -mmcu=msp430g2553 -o blink.elf blink.c`
- Flash the executable to your msp430 `mspdebug rf2500 'prog blink.elf'`
