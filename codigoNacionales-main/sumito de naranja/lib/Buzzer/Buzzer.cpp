#include<Arduino.h>
#include"Buzzer.h"
Buzzer::Buzzer(int pin)
  {
    _pin = pin;
    pinMode(pin, OUTPUT);
  }
  void Buzzer::Encender()
  {
    digitalWrite(_pin, HIGH);
  }
  void Buzzer::Apagar()
  {
    digitalWrite(_pin, LOW);
  }