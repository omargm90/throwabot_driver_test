#ifndef RAMPFUNCTIONS_H
#define RAMPFUNCTIONS_H

#include "../ProfileTestDefines.h"

#define K_FREQ_SLOW 1600
#define K_FREQ_FAST 2400 //(1600-400)/(0.5)
#define Y0_FREQ_FAST -800

#define PLATEAU_TIME 500 // ms
#define DELTAX_UP 0.01
#define DELTAX_DOWN -0.01

struct RampStruct{
    float kSlope = K_FREQ_SLOW;
    float y0 = 0;
    bool slowState = true;
};

enum RampState{
  rampUp,
  plateauUp,
  rampDown,
  plateauDown
};


float updateDeltaX(RampState &rampStateVal, float &x, float &timePlateau);
RampStruct updateRampParams(RampStruct rampVals, float x);

#endif

