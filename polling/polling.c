#include <msp430.h>

int main(void) {

  // Stop watchdog timer to prevent time out reset
  WDTCTL = WDTPW | WDTHOLD;
  // Sets Digitally Controlled Oscilator(DCO) range to 1MHZ
  BCSCTL1 = CALBC1_1MHZ;
  DCOCTL = CALDCO_1MHZ;

  // P1 Resistor ENable: enables pullup resistor on P1.3
  P1REN   |= BIT3; 
   // P1 Output: Configure P1.3 button as pull-up
  P1OUT   |= BIT3; 
  // P1 Direction: Set P1DIR with P0 to high
  P1DIR   |= BIT0;

// Creates an infinite loop waiting for the button to be pressed
  for (;;) {
    // If not P1 input AND BIT3 
    if (!(BIT3 & P1IN)) {
      // Toggle LED at P1.0
      P1OUT ^= BIT0;
// Delays input after the button is pressed so that it doesnt turn off again
      while (!(BIT3 & P1IN)) {}
      __delay_cycles(32000);
    }
  }

  return 0;
}

