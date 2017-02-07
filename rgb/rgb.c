#include <msp430.h>
// Note: 0b00000001 = BIT0

void rgb(char RED, char GREEN, char BLUE) {
  P1OUT = RED << 1 | GREEN << 2 | BLUE << 3;
}

int main(void) {

  // Stop watchdog timer to prevent time out reset
  WDTCTL = WDTPW | WDTHOLD;
  // Sets Digitally Controlled Oscilator(DCO) range to 1MHZ
  BCSCTL1 = CALBC1_1MHZ;
  DCOCTL = CALDCO_1MHZ;

  // Sets the P1.1, P1.2 and P1.3 direction to output
  // This is equivelant to P1DIR = BIT1+BIT2+BIT3;
  P1DIR = 0b00001110;

// Infinite loop changing the LED color
  for (;;) {
    rgb(0, 0, 0);
    __delay_cycles(1000000);
    rgb(1, 0, 0);
    __delay_cycles(1000000);
    rgb(1, 1, 0);
    __delay_cycles(1000000);
    rgb(0, 1, 0);
    __delay_cycles(1000000);
    rgb(0, 1, 1);
    __delay_cycles(1000000);
    rgb(0, 0, 1);
    __delay_cycles(1000000);
    rgb(1, 0, 1);
    __delay_cycles(1000000);
    rgb(1, 1, 1);
    __delay_cycles(1000000);

  }
  return 0;
}
