#include <msp430.h>

// If the char entered is 1 it turns on that LED segment
// RED -> P1.1 -> BIT1
// GREEN -> P1.2 -> BIT2
// Blue -> P1.3 -> BIT3
void rgb(char RED, char GREEN, char BLUE) {
  P1OUT = RED << 1 | GREEN << 2 | BLUE << 4;
}

int main(void) {

  // Stop watchdog timer to prevent time out reset
  WDTCTL = WDTPW | WDTHOLD;
  // Sets Digitally Controlled Oscilator(DCO) range to 1MHZ
  BCSCTL1 = CALBC1_1MHZ;
  DCOCTL = CALDCO_1MHZ;

  // Sets the P1.1, P1.2 and P1.3 direction to output
  // This is equivalent to P1DIR = BIT1+BIT2+BIT3;
  P1DIR   = ~BIT3;

// Infinite loop changing the LED color
  for (;;) {
    // none = no color
    rgb(0, 0, 0);
    __delay_cycles(1000000);
    // BIT1 = RED
    rgb(1, 0, 0);
    __delay_cycles(1000000);
    // BIT1+BIT2 = RED+GREEN = YELLOW
    rgb(1, 1, 0);
    __delay_cycles(1000000);
    // BIT2 = GREEN
    rgb(0, 1, 0);
    __delay_cycles(1000000);
    // BIT2+BIT3 = GREEN+BLUE = CYAN
    rgb(0, 1, 1);
    __delay_cycles(1000000);
    // BIT3 = BLUE
    rgb(0, 0, 1);
    __delay_cycles(1000000);
    // BIT1+BIT3 = RED+BLUE = PURPLE
    rgb(1, 0, 1);
    __delay_cycles(1000000);
    // BIT1+BIT2+BIT3 = RED+GREEN+BLUE = WHITE
    rgb(1, 1, 1);
    __delay_cycles(1000000);

  }
  return 0;
}
