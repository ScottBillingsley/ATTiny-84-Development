/*
 *              AtTiny 84 Development 
 *              
 *              
 *                    ----U--- 
 *              VCC -| 1    14|- GND
 *              PB0 -| 2    13|- PA0
 *              PB1 -| 3    12|- PA1
 *              PB3 -| 4    11|- PA2
 *              PB2 -| 5    10|- PA3
 *              PA7 -| 6     9|- PA4
 *              PA6 -| 7     8|- PA5
 *                    --------
 */

/************************* Defines ********************************/

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


  /************************* Setup Pins ***************************/



}/**************************  End Setup **************************/


/******************************************************************/
/**************************** Loop ********************************/
/******************************************************************/
void loop() {


}/*************************** End Loop *****************************/
