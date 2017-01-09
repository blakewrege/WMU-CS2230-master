#include <msp430.h>

int main(void) {

  // Stop watchdog timer to prevent time out reset
  WDTCTL = WDTPW | WDTHOLD; 
  // Sets Digitally Controlled Oscilator(DCO) range to 1MHZ
  BCSCTL1 = CALBC1_1MHZ;
  DCOCTL = CALDCO_1MHZ;

// Sets the P1.0 direction to output 
  P1DIR = 0b00000001;
// Sets P1.0 to high causing the LED to turn on
  P1OUT = 0b00000001;

// Infinite loop turning the LED off and on
  for(;;) {
    P1OUT = 0b00000000;
    __delay_cycles(1000000);
	P1OUT = 0b00000001;
    __delay_cycles(1000000);
  }
  return 0;
}
