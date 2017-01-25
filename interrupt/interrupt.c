#include <msp430.h>

int main(void) {

  // Stop watchdog timer to prevent time out reset
  WDTCTL = WDTPW | WDTHOLD;
  // Sets Digitally Controlled Oscilator(DCO) range to 1MHZ
  BCSCTL1 = CALBC1_1MHZ;
  DCOCTL = CALDCO_1MHZ;

  // P1 Direction: Set P1.0 to output, else input
  P1DIR    = BIT0;
  // P1 Resistor ENable: enables pullup resistor on P1.3
  P1REN    = BIT3;
  // P1 Output: Configure P1.3 button as pull-up
  P1OUT   |= BIT3;
  // P1 Interrupt Enable: Enables interrupt for P1.3 
  P1IE    |= BIT3;
  // P1 Interrupt Enable Sensitive: sets P1.3 to high/low edge
  P1IES   |= BIT3;
  // P1 Interrupt Flag: Set interrupt pending on P1.3
  P1IFG   &= ~BIT3;

// Enable all interrupts
  _BIS_SR(LPM4_bits | GIE);
}

// Pragma communicates to the C compiler that the following
// code is to be treated as the interrupt vector for the MSP430
#pragma vector=PORT1_VECTOR
__interrupt void Port_1(void)
{
  // Toggle LED at P1.0
  P1OUT ^= BIT0;
  while (!(BIT3 & P1IN)) {}
  __delay_cycles(32000);

  P1IFG &= ~BIT3;

  return 0;
}
