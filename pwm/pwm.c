#include <msp430.h>

main(void) {
  // Stop watchdog timer to prevent time out reset
  WDTCTL = WDTPW | WDTHOLD;
  // Sets Digitally Controlled Oscilator(DCO) range to 1MHZ
  BCSCTL1 = CALBC1_1MHZ;
  DCOCTL = CALDCO_1MHZ;

// P1 Direction: Set P1.6 to output
// Also equals P1DIR = P1DIR | BIT6
  P1DIR   |= BIT6;

// P1 Select: Set P1.6 to output direction
// P1.6 is controlled by Pulse width modulation in this
  P1SEL   |= BIT6;

  // Capture Compare Register Timer0_A3:
  // Holds the 16-bit count value for the counter(max 0xFFFF)
  TA0CCR0 = 284 - 1;
  // Capture Compare Control Timer0_A3: Controls the PWM output in this
  // OUTMOD_4: Toggles P1.6 everytime TA0CCR1(not set so equals 0) is hit
  TA0CCTL1 = OUTMOD_4;
  // Timer_A control: Configure and start the timer
  // TASSEL_2: Timer A clock source select to Sub Master Clock(SMCLK)
  // MC_1: Timer A mode control, counts up to TA0CCR0
  // ID_3: Timer A input divider, divides input by 8
  TA0CTL = TASSEL_2 + MC_1 + ID_3;
  // Sets the msp430 to Low Power Mode 1
  LPM1;
}
