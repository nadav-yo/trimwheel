// Encoder.h
#ifndef ENCODER_h
#define ENCODER_h

#include <Arduino.h>

class Encoder {
  private:
      int pin1;
      int pin2;
      int prevState;
      int rotDir;
      int rotVal;
      int resolution;

  public:
    Encoder(int pin1, int pin2, int resolution);
    void init();
    boolean shouldUpdate();
    int getState();
};

#endif
