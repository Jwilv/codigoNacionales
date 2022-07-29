#include "Switch.h"
#include <Arduino.h>
Switch::Switch(int pin)
  {
    _switchPin = pin;
    pinMode(_switchPin, INPUT);
  }

  bool Switch::getEstado()
  {
    bool estado = digitalRead(_switchPin);
    return estado;
  }
