#ifndef Switch_h
#define Switch_h
#include <Arduino.h>
class Switch
{
private:
  int _switchPin;

public:
  Switch(int pin);
  bool getEstado();
};
#endif