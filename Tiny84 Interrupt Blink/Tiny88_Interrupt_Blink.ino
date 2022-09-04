/*
                Tiny88 Interrupt Blink
                Vernon Billingsley 2022

                Set up the interrupt pin D2 and
                blink LED on pin D8

                         ATTiny88
                     -----------------
               Pin  -|                |-  D2 PD2  INT0
               GND  -|                |-  D1 PD1  TXD
               5v   -|                |-  D0 PD0  LED RXD
    OC2B  PD3   D3  -|                |-  RST
          PD4   D4  -|                |-  D25 PC7
    OC0B  PD5   D5  -|                |-  D24 ADC5  SCL PC5
    AIN0  PD6   D6  -|                |-  D23 ADC4  SDA PC4
    AIN1  PD7   D7  -|                |-  D22 ADC3  PC3
          PB0   D8  -|                |-  D21 ADC2  PC2
    OC1A  PB1   D9  -|                |-  D20 ADC1  PC1
  OC1B  SS  PB2   D10 -|                |-  D19 ADC0  PC0
    MOSI  PB3   D11 -|                |-  D18 ADC7  PA1
    MISO  PB4   D12 -|      -----     |-  D17 ADC6  PA0
     SCK  PB5   D13 -|     | USB |    |-  D16 PA3
          PB7   D14 -|     |     |    |-  D15 PA2
                      -----------------

      Pin       Function
      ---------------------
      D2        Interrupt IN, 10k resistor to GND

      D8        LED OUT

*/

/************************* Defines ********************************/
#define DEBUG 0

#if DEBUG == 1
#define dprint(expression) Serial.print("# "); Serial.print( #expression ); Serial.print( ": " ); Serial.println( expression )
#define dshow(expression) Serial.println( expression )
#else
#define dprint(expression)
#define dshow(expression)
#endif

#ifndef cbi
#define cbi(sfr, bit) (_SFR_BYTE(sfr) &= ~_BV(bit))
#endif
#ifndef sbi
#define sbi(sfr, bit) (_SFR_BYTE(sfr) |= _BV(bit))
#endif


/************************** Variables *****************************/


/**************************  Functions ****************************/


/******************************************************************/
/*************************** Setup ********************************/
/******************************************************************/
void setup() {
  if (DEBUG) {
    Serial.begin(115200);
  }

  /************************* Setup Pins ***************************/
  /* Pin D2 as INPUT for Interrupt */
  DDRD &= ~_BV (2);

  /* Pin D8 as OUTPUT for LED */
  DDRB |= _BV (0);

  /* Setup Pin 2 interrupt  CHANGE */
  cbi(EICRA, ISC01);
  sbi(EICRA, ISC00);
  sbi(EIMSK, INT0);
  sei(); // allow interrupts


}/**************************  End Setup **************************/
/* Pin 2 interrupt ISR  */
ISR(INT0_vect, ISR_BLOCK)
{
  /* Read the interrutp pin and set the LED */
  if ((PIND >> 2) & 0x01 == 1) {
    /* If the interrupt pin D2 is HIGH turn on LED */
    PORTB |= _BV (0);
  }else{
    /* If the interrutp pin D2 is LOW turn off LED */
    PORTB &= ~_BV (0);
  }
}


/******************************************************************/
/**************************** Loop ********************************/
/******************************************************************/
void loop() {




}/*************************** End Loop *****************************/
