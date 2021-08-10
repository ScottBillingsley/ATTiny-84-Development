/*
                AtTiny 84 Development
             Setup Timer 1 to toggle a pin, PB0

                      ----U---
                VCC -| 1    14|- GND
                PB0 -| 2    13|- PA0
                PB1 -| 3    12|- PA1
                PB3 -| 4    11|- PA2
                PB2 -| 5    10|- PA3
                PA7 -| 6     9|- PA4
                PA6 -| 7     8|- PA5
                      --------
*/

/************************* Defines ********************************/

#ifndef cbi
#define cbi(sfr, bit) (_SFR_BYTE(sfr) &= ~_BV(bit))
#endif
#ifndef sbi
#define sbi(sfr, bit) (_SFR_BYTE(sfr) |= _BV(bit))
#endif

#define PIN_PORT PORTB
#define PORT_DIR DDRB
#define PIN_BIT 0


/************************** Variables *****************************/
volatile boolean flip = true;

/**************************  Functions ****************************/


/******************************************************************/
/*************************** Setup ********************************/
/******************************************************************/
void setup() {


  /************************* Setup Pins ***************************/
  /* Set pin PB0 to OUTPUT */
  PORT_DIR |= _BV (PIN_BIT);


  /*************************  Setup Timer1 ************************/
  cli();                /*  stop interrupts */
  /*set timer1  */
  TCCR1A = 0;/* set entire TCCR1A register to 0 */
  TCCR1B = 0;/* same for TCCR1B */
  TCNT1  = 0;/* initialize counter value to 0 */
  /* Measured speed 8.16 mHz    */
  /* set compare match register */
  OCR1A = 4080; /*1000 Hz */
  /* turn on CTC mode */
  cbi(TCCR1A, WGM10);
  cbi(TCCR1A, WGM11);
  sbi(TCCR1B, WGM12);
  cbi(TCCR1B, WGM13);
  /*  Set prescaler to 1 */
  cbi(TCCR1B, CS12);
  cbi(TCCR1B, CS11);
  sbi(TCCR1B, CS10);
  /* enable timer compare interrupt */
  sbi(TIMSK1, OCIE1A);
  sei();                /*  allow interrupts  */

}/**************************  End Setup **************************/

ISR(TIM1_COMPA_vect) {
  flip = !flip;
  if (flip) {
    /* HIGH */
    PIN_PORT |= _BV (PIN_BIT);
  } else {
    /* LOW */
    PIN_PORT &= ~_BV (PIN_BIT);
  }
}

/******************************************************************/
/**************************** Loop ********************************/
/******************************************************************/
void loop() {


}/*************************** End Loop *****************************/
