// Encoder.cpp
#include "Encoder.h"

Encoder::Encoder(int pin1, int pin2, int resolution) {
  this->pin1 = pin1;
  this->pin2 = pin2;
  this->resolution = resolution;
  pinMode(pin1, INPUT_PULLUP);
  pinMode(pin2, INPUT_PULLUP);
}

void Encoder::init() {
  pinMode(this->pin1, INPUT_PULLUP);
  pinMode(this->pin2, INPUT_PULLUP);
}

int Encoder::getState() {
  return this->rotVal;
}

boolean Encoder::shouldUpdate() {
  if (Serial.available() > 1)
  {
    this->rotVal = (Serial.read() << 8) | Serial.read();
  }
  boolean shouldUpdate;
  int CurrStateAB = (digitalRead(this->pin1) << 1) | digitalRead(this->pin2);

  if (this->prevState != CurrStateAB)
  {
    int PrevCurrStateAB = (this->prevState << 2) | CurrStateAB;
    if ((PrevCurrStateAB == 0b1101) || (PrevCurrStateAB == 0b0010)) this->rotDir = 1;
    else if ((PrevCurrStateAB == 0b1110) || (PrevCurrStateAB == 0b0001)) this->rotDir = -1;
    else if ((PrevCurrStateAB == 0b0100) || (PrevCurrStateAB == 0b1011))
    {
      if ((this->rotDir == 1) && (this->rotVal < resolution)) {
        this->rotVal++;
        shouldUpdate = true;
      }
    }
    else if ((PrevCurrStateAB == 0b1000) || (PrevCurrStateAB == 0b0111))
    {
      if ((this->rotDir == -1) && (this->rotVal > -resolution)) {
        this->rotVal--;
        shouldUpdate = true;
      }
    }
    this->prevState = CurrStateAB;
  }
  return shouldUpdate;
}
