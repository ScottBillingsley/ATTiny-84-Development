/*
               AtTiny 85 Development
              Vernon Billingsley 2023

          Fade and LED on chip pin 6 using Timer1 
          in the PWM mode....

                     ----U---
             Reset -| 1     8|- Vcc
               PB3 -| 2     7|- PB2   SCL SCK
               PB4 -| 3     6|- PB1       MISO  OC1A
               GND -| 4     5|- PB0   SDA MOSI
                     --------

*/


/************************* Defines ********************************/

#ifndef cbi
#define cbi(sfr, bit) (_SFR_BYTE(sfr) &= ~_BV(bit))
#endif
#ifndef sbi
#define sbi(sfr, bit) (_SFR_BYTE(sfr) |= _BV(bit))
#endif

/************************** Variables *****************************/
volatile uint8_t fade;
volatile boolean up = true;


/**************************  Functions ****************************/


/******************************************************************/
/*************************** Setup ********************************/
/******************************************************************/
void setup() {

  /************************* Setup Pins ***************************/
  /*Set PORT B  Pin 1, chip pin 6, OC1A,  to OUTPUT */
  DDRB |= _BV (1);

  /******** Setup Timer 1 ***********************/
  /* Disable interrupts */
  cli();
  /* Enable PWM Mode */
  sbi(TCCR1, PWM1A);
  /* Enable the OC1A pin, Set on match */
  sbi(TCCR1, COM1A1);
  cbi(TCCR1, COM1A0);
  /* Prescale to 1024 */
  sbi(TCCR1, CS13);
  cbi(TCCR1, CS12);
  sbi(TCCR1, CS11);
  sbi(TCCR1, CS10);
  /* Enable the interrupt vector */
  sbi(TIMSK, OCIE1A);
  /* Preload counter */
  OCR1A = 64;

  /* Enable interrupts */
  sei();

}/**************************  End Setup **************************/
ISR(TIM1_COMPA_vect) {
  if (up == true) {
    fade ++;
    if (fade == 64) {
      up = false;
    }
  }
  if (up == false) {
    fade --;
    if(fade == 1){
      up = true;
    }

  }
  OCR1A = fade;
}


/******************************************************************/
/**************************** Loop ********************************/
/******************************************************************/
void loop() {


}/*************************** End Loop *****************************/
