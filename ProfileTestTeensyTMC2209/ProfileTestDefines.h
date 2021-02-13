#include <TMCStepper.h>

#define DIAG          2 // Diagnosis
#define DIR_PIN       3 // Direction
#define STEP_PIN      4 // Step
#define SPREAD        5 // Chopper mode selection
#define MS2_PIN       6 // UART address bit 1
#define MS1_PIN       9 // UART address bit 0
#define EN_PIN        10// Enable

#define SERIAL_PORT Serial3 // RX pin 7, TX pin 8
#define DRIVER_ADDRESS 0b00 // TMC2209 Driver address according to MS1 and MS2

#define R_SENSE 0.11f // Match to your driver
                      // SilentStepStick series use 0.11
                      // UltiMachine Einsy and Archim2 boards use 0.2
                      // Panucatt BSD2660 uses 0.1
                      // Watterott TMC5160 uses 0.075
#define LOW_FREQ_THLD 12
#define DELTATIME 10
