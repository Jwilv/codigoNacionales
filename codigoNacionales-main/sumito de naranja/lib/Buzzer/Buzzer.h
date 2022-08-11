#ifndef Buzzer_h
#define Buzzer_h
#include <Arduino.h>
class Buzzer
{
private:
  int _pin;

public:
  Buzzer(int pin);
  void Encender();
  void Apagar();
};
#endif