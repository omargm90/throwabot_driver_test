#include "RampFunctions.h" 
#include <Arduino.h>

float updateDeltaX(RampState &rampStateVal, float &x, float &timePlateau){
  // *can I update locally? or should i pass by reference
  
  switch (rampStateVal)
  {
  case rampUp:
    if(x>=1)
    {
      x = 1;
      // Serial.println("");
      // Serial.print("state: "); Serial.println(rampStateVal);
      rampStateVal = plateauUp;
      // Serial.print("state: "); Serial.println(rampStateVal);
      // Serial.print("delta X: "); Serial.println(0);
      timePlateau = millis();
      return 0;
    }
    return DELTAX_UP;
    break;

  case plateauUp:
    if( (millis() - timePlateau) > PLATEAU_TIME){
      // Serial.println("");
      // Serial.print("state: "); Serial.println(rampStateVal);
      rampStateVal = rampDown;
      // Serial.print("state: "); Serial.println(rampStateVal);
      // Serial.print("delta X: "); Serial.println(DELTAX_DOWN);
      return DELTAX_DOWN;
    }
    return 0;
    break;

  case rampDown:
    if(x<=0)
    {
      x = 0;
      // Serial.println("");
      // Serial.print("state: "); Serial.println(rampStateVal);
      rampStateVal  = plateauDown;
      // Serial.print("state: "); Serial.println(rampStateVal);
      // Serial.print("delta X: "); Serial.println(0);
      timePlateau   = millis(); 
      return 0;
    }
    return DELTAX_DOWN;
  break;

  case plateauDown:
    if( (millis() - timePlateau) > PLATEAU_TIME){
      // Serial.println("");
      // Serial.print("state: "); Serial.println(rampStateVal);
      rampStateVal = rampUp;
      // Serial.print("state: "); Serial.println(rampStateVal);
      // Serial.print("delta X: "); Serial.println(DELTAX_UP);
      return DELTAX_UP;
    }
    return 0;
    break;
  
  default:
    return 0;
    break;
  }
}

RampStruct updateRampParams(RampStruct rampVals, float x, TMC2209Stepper &driver){
  if(x > 0.5 && rampVals.slowState){
    // Serial.println("fast state");
    driver.microsteps(32);          // Set microsteps to 1/32th
    return {
      K_FREQ_FAST,
      Y0_FREQ_FAST,
      false //slowState
    };
  }
  else if(x <= 0.5 && !rampVals.slowState){
    // Serial.println("slow state");
    driver.microsteps(32);          // Set microsteps to 1/32th
    return {
      K_FREQ_SLOW,
      0,
      true //slowState
    };

  }   
  else {
      return rampVals;
  }
}