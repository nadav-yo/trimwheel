
#include <Joystick.h>
#include "Encoder.h"

// inputs
#define BUTTON_PIN 6
// 1st encoder 
#define ROTPIN_A 7
#define ROTPIN_B 8

// variables
#define ROT_RESOLUTION 127 /* 1 impulse = 100%/255 = 0.4% of max trim */

Joystick_ Joystick(JOYSTICK_DEFAULT_REPORT_ID, JOYSTICK_TYPE_GAMEPAD,
  1, 0,                  // Button Count, Hat Switch Count
  false, false, false,    // no X Y Z axis
  false, false, false,   // No Rx, Ry, or Rz
  false, true,          // No rudder or, only throttle
  false, false, false);  // No accelerator, brake, or steering 


Encoder encoder1(ROTPIN_A, ROTPIN_B, ROT_RESOLUTION);

void setup() {  
  encoder1.init();
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  Serial.begin(9600);
  Joystick.begin();
  Joystick.setThrottleRange(-ROT_RESOLUTION, ROT_RESOLUTION);
}

boolean isButtonPushDown(int pin){
  return !digitalRead(pin);
}

void loop()
{
  if (encoder1.shouldUpdate()) {
    Joystick.setThrottle(encoder1.getState());
  }
  Joystick.setButton(0, isButtonPushDown(BUTTON_PIN));
}
