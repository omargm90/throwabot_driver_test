#include "ProfileTestDefines.h"
#include "src/RampFunctions.h"

float freq = 0;
bool dir_sign = LOW;
float deltaX = 0;
float x = 0;

RampStruct rampParams;
RampState rampCurrentState;

TMC2209Stepper driver(&SERIAL_PORT, R_SENSE, DRIVER_ADDRESS);

void setup() {
  //initialize 

  Serial.begin(9600);

  rampCurrentState = plateauDown;

  pinMode(EN_PIN, OUTPUT);
  pinMode(STEP_PIN, OUTPUT);
  pinMode(DIR_PIN, OUTPUT);
  pinMode(MS2_PIN, OUTPUT);
  pinMode(MS1_PIN, OUTPUT);
  
  digitalWrite(EN_PIN, LOW);      // Enable driver in hardware
  digitalWrite(MS2_PIN, LOW);     
  digitalWrite(MS1_PIN, LOW);     
                                 
  SERIAL_PORT.begin(115200);      // HW UART drivers

  driver.begin();                 
                                  
  driver.toff(5);                 // Enables driver in software
  driver.rms_current(600);        // Set motor RMS current
  driver.microsteps(32);          // Set microsteps to 1/32th

  driver.pwm_autoscale(true);     // Needed for stealthChop
}

float time = millis();
float time_0 = time;
float time_p = time_0;
float time_n = 0;

void loop() {
  time_n = millis();
  if ((time_n - time_0) <= 3230*1.25){

  if (time_n - time > DELTATIME) { 
    
    deltaX = updateDeltaX(rampCurrentState, x, time_p); 
    rampParams = updateRampParams(rampParams, x, driver);

    freq = rampParams.kSlope * x + rampParams.y0;
    
    Serial.println(x*100);

    if(freq>LOW_FREQ_THLD){
      driver.toff(5);                 // Enables driver in software
    }
    else{
      driver.toff(0);                 // Disables driver in software
      freq = 0;
    }
    
    analogWriteFrequency(STEP_PIN, freq);
    analogWrite(STEP_PIN, 128);

    x = constrain(x + deltaX, 0, 1);
    time = millis();   

  }
  }
  else
  {
     driver.toff(0);                 // Disables driver in software
    analogWriteFrequency(STEP_PIN, 0);    
  }
}
 
