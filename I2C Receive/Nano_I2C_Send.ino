/*
                  AtTiny 84 Development
              I2C Master Send using arduino Nano  
              
               Send the state of the button to an ATTiny84
              using I2C, print the state of the button to the
              serial monitor..

              Button on pin 2, normally HIGH
              LED on pin 3

              A4    SDA
              A5    SCL
  
 */

#include <elapsedMillis.h>
#include <Wire.h>

/************************* Defines ********************************/
#define DEBUG 1

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

/* Bus ID of the ATTiny */
#define VOICE_1 20

/************************** Variables *****************************/
/* Used to only send byte on button press and button release */
boolean button_on = false;

/**************************  Functions ****************************/
void send_a_byte(byte b){
  Wire.beginTransmission(VOICE_1);
  Wire.write(b); 
  Wire.endTransmission();
}

/******************************************************************/
/*************************** Setup ********************************/
/******************************************************************/
void setup() {
  if (DEBUG) {
    Serial.begin(115200);
  }
  Wire.begin();

  /************************* Setup Pins ***************************/
  DDRD &= ~_BV (2); // pinMode (2, INPUT);
  PORTD |= _BV (2); // digitalWrite (2, HIGH);

  DDRD |= _BV (3); // pinMode (3, OUTPUT);

}/**************************  End Setup **************************/

/* debounce timer */
elapsedMillis button_time;

/******************************************************************/
/**************************** Loop ********************************/
/******************************************************************/
void loop() {

  if (button_time > 125) {
    /* Read the state of the button */
    byte b = (PIND & _BV (2));

    if (b == 0 && !button_on) {
      PORTD |= _BV (3); // digitalWrite (3, HIGH);
      button_time = 0;
      Serial.println("ON");
      send_a_byte(42);
      button_on = true;
    }
    if (b != 0 && button_on) {
      PORTD &= ~_BV (3); // digitalWrite (2, LOW);
      Serial.println("OFF");
      send_a_byte(1);
      button_on = false;
    }
    
  }



}/*************************** End Loop *****************************/
