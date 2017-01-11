#include <msp430.h>

int main(void) {

  // Stop watchdog timer to prevent time out reset
  WDTCTL = WDTPW | WDTHOLD; 
  // Sets Digitally Controlled Oscilator(DCO) range to 1MHZ
  BCSCTL1 = CALBC1_1MHZ;
  DCOCTL = CALDCO_1MHZ;

  P1DIR    =BIT0;
  P1REN    =BIT3;
  P1OUT   |=BIT3;
  P1IE    |=BIT3;
  P1IES   |=BIT3;
  P1IFG   &= ~BIT3;

  _BIS_SR(LPM4_bits | GIE);
} 

// Pragma communicates to the C compiler that the following 
// code is to be treated as the interrupt vector for the MSP430
#pragma vector=PORT1_VECTOR
  __interrupt void Port_1(void)
{
  P1OUT ^= BIT0;
  while (!(BIT3 & P1IN)) {}
        __delay_cycles(32000);
    
  P1IFG &= ~BIT3;

  return 0;
}
