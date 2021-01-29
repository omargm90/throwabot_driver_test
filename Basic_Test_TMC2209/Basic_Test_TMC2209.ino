#include "TMCStepper.h"
#include "Tone.h"

#define EN_PIN           38 // Enable
#define DIR_PIN          55 // Direction
#define STEP_PIN         54 // Step

#define SERIAL_PORT_TMC Serial // 
#define BAUD_RATE 57600
#define DRIVER_ADDRESS 0b00 // TMC2209 Driver address according to MS1 and MS2

#define R_SENSE 0.11f // SilentStepStick series use 0.11

//init object driver
TMC2209Stepper driver(&SERIAL_PORT, R_SENSE, DRIVER_ADDRESS);

void setup() {
  //initialize 
  pinMode(EN_PIN, OUTPUT);
  pinMode(STEP_PIN, OUTPUT);
  pinMode(DIR_PIN, OUTPUT);

  SERIAL_PORT_TMC.begin(BAUD_RATE);      // HW UART drivers
  driver.beginSerial(BAUD_RATE);     // SW UART drivers

  driver.toff(5);                 // Enables driver in software
  driver.rms_current(600);        // Set motor RMS current
  driver.microsteps(16);          // Set microsteps to 1/16th

//driver.en_pwm_mode(true);       // Toggle stealthChop on TMC2130/2160/5130/5160
//driver.en_spreadCycle(false);   // Toggle spreadCycle on TMC2208/2209/2224
  driver.pwm_autoscale(true);     // Needed for stealthChop
  
  digitalWrite(EN_PIN, LOW);      // Enable driver in hardware
}

void loop() {
  // put your main code here, to run repeatedly:

}
