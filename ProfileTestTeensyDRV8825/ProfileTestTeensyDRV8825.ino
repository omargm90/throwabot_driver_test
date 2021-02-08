#include "ProfileTestDefines.h"
#include "src/RampFunctions.h"

float freq = 0;
bool dir_sign = LOW;
float deltaX = 0;
float x = 0;

RampStruct rampParams;
RampState rampCurrentState;

void setup() {
  //initialize 

  Serial.begin(9600);

  rampCurrentState = plateauDown;

  pinMode(RST_PIN, OUTPUT);
  digitalWrite(RST_PIN, HIGH);
  
  pinMode(DIR_PIN, OUTPUT);
  pinMode(STEP_PIN, OUTPUT);
  pinMode(SLEEP_PIN, OUTPUT);
  pinMode(M2_PIN, OUTPUT);
  pinMode(M1_PIN, OUTPUT);
  pinMode(M0_PIN, OUTPUT);
  pinMode(EN_PIN, OUTPUT);

  digitalWrite(DIR_PIN, dir_sign);    
  digitalWrite(SLEEP_PIN, LOW);
  
  digitalWrite(M0_PIN, LOW);
  digitalWrite(M1_PIN, LOW);
  digitalWrite(M2_PIN, HIGH);
  digitalWrite(EN_PIN, LOW);      // Enable driver in hardware  
}

float time = millis();
float time_0 = time;
float time_p = time_0;
float time_n = 0;

void loop() {
  time_n = millis();
  if ((time_n - time_0) <= 3230){

  if (time_n - time > DELTATIME) { 
    
    deltaX = updateDeltaX(rampCurrentState, x, time_p); 
    rampParams = updateRampParams(rampParams, x);

    freq = rampParams.kSlope * x + rampParams.y0;
    
    Serial.println(x*100);

    if(freq>LOW_FREQ_THLD){
      digitalWrite(SLEEP_PIN, HIGH);
    }
    else{
      digitalWrite(SLEEP_PIN, LOW);
      freq = 0;
    }
    
    // digitalWrite(DIR_PIN, dir_sign);
    analogWriteFrequency(STEP_PIN, freq);
    analogWrite(STEP_PIN, 128);

    x = constrain(x + deltaX, 0, 1);
    time = millis();   

  }
  }
  else
  {
    digitalWrite(SLEEP_PIN, LOW);
    analogWriteFrequency(STEP_PIN, 0);    
  }
}
 
