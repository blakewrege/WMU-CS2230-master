# Button Interrupt Tutorial 
[![Alt text](https://img.youtube.com/vi/N7KS2FEHrIs/0.jpg)](https://www.youtube.com/watch?v=N7KS2FEHrIs)(click image for video)
<br>Tutorial outlining how to use interrupts instead of polling to source the Lauchpad's on-board switch to control an on-board LED.
## Materials
- MSP430
- Breadboard
- 2 Jumper Wires
- 5mm Red LED

## Steps
- Insert the LED into the breadboard
- Connect a jumper cable to P1.0 and the breadboard in same row as the LED
- Connect the other jumper cable to GND and the breadboard in same row as the LED(next to the other)
- Create the executable by running `make`
- Flash the executable to your msp430 `sudo make flash`
