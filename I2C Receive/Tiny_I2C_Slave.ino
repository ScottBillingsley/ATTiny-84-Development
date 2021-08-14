/*
                AtTiny 84 Development
                I2C Slave reader

          Read a byte sent from the arduino master and 
         set the LED on or off acording to the byte received..      

         Example using lucullusTheOnly TinyWire library
         https://github.com/lucullusTheOnly/TinyWire

                      ----U---
                VCC -| 1    14|- GND
                PB0 -| 2    13|- PA0
                PB1 -| 3    12|- PA1
                PB3 -| 4    11|- PA2
                PB2 -| 5    10|- PA3
                PA7 -| 6     9|- PA4
                PA6 -| 7     8|- PA5
                      --------

                   Pins    Function
                   1         VCC
                   2         LED
                   3
                   4         Reset
                   5
                   6
                   7         SDA
                   8
                   9         SCL
                   10
                   11
                   12
                   13
                   14       GND
*/
#include <TinyWire.h>


/************************* Defines ********************************/

#ifndef cbi
#define cbi(sfr, bit) (_SFR_BYTE(sfr) &= ~_BV(bit))
#endif
#ifndef sbi
#define sbi(sfr, bit) (_SFR_BYTE(sfr) |= _BV(bit))
#endif

#define I2C_SLAVE_ADDRESS 20

/************************** Variables *****************************/


/**************************  Functions ****************************/
void receiveEvent(int howMany) {

  while (TinyWire.available() > 0) {
    byte r = TinyWire.read();
    if (r == 42) {
      PORTB |= _BV (0);
    }
    if (r == 1) {
      /* Pin LOW */
      PORTB &= ~_BV (0);
    }

  }
}

/******************************************************************/
/*************************** Setup ********************************/
/******************************************************************/
void setup() {
  TinyWire.begin(I2C_SLAVE_ADDRESS);
  TinyWire.onReceive(receiveEvent);

  /************************* Setup Pins ***************************/
  /* Pin PB0, chip pin 2 as OUTPUT */
  DDRB |= _BV (0);


}/**************************  End Setup **************************/


/******************************************************************/
/**************************** Loop ********************************/
/******************************************************************/
void loop() {


}/*************************** End Loop *****************************/
