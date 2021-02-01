#include "TMCStepper.h"
#include "Tone.h"

#define EN_PIN           2 // Enable
#define DIR_PIN          3 // Direction
#define STEP_PIN         10 // Step

#define SERIAL_PORT_TMC Serial // 
#define BAUD_RATE 57600
#define DRIVER_ADDRESS 0b00 // TMC2209 Driver address according to MS1 and MS2

#define R_SENSE 0.11f // SilentStepStick series use 0.11

#define FREQ_MAX 5000
#define LOW_SPEED_THLD 0.015
#define DELTATIME 10

#define JoyStick_X A0 // X-axis-signal
#define JoyStick_Y A1 // Y-axis-signal

float freq = 0;
float x = 0;
float y = 0;
bool dir_sign = LOW;

//init object driver
TMC2209Stepper driver(&SERIAL_PORT_TMC, R_SENSE, DRIVER_ADDRESS);

Tone driver_pwm;

void setup() {
  
  //initialize 
  pinMode(EN_PIN, OUTPUT);
  pinMode(STEP_PIN, OUTPUT);
  pinMode(DIR_PIN, OUTPUT);

  pinMode (JoyStick_X, INPUT);
  pinMode (JoyStick_Y, INPUT);

  SERIAL_PORT_TMC.begin(BAUD_RATE);  // HW UART drivers
//  driver.beginSerial(BAUD_RATE);     // SW UART drivers

  driver.toff(5);                 // Enables driver in software
  driver.rms_current(600);        // Set motor RMS current
  driver.microsteps(16);          // Set microsteps to 1/16th

//driver.en_pwm_mode(true);       // Toggle stealthChop on TMC2130/2160/5130/5160
//driver.en_spreadCycle(false);   // Toggle spreadCycle on TMC2208/2209/2224
  driver.pwm_autoscale(true);     // Needed for stealthChop

  driver_pwm.begin(STEP_PIN);

  digitalWrite(DIR_PIN, dir_sign);  
  digitalWrite(EN_PIN, LOW);      // Enable driver in hardware
  
}

float time = millis();

void loop() {

  if (millis() - time > DELTATIME) {  
    y = (analogRead(JoyStick_X) - 511.5 ) / 511.5;

    if ( y < 0)
    dir_sign = HIGH; 
    else
    dir_sign = LOW;

    y *=y;

    if(y>LOW_SPEED_THLD){
      freq = y * FREQ_MAX;
      driver_pwm.play(freq); 
    }
    else{
      freq = 0;
      driver_pwm.stop();    
    }
    
    time = millis();
  }

}
