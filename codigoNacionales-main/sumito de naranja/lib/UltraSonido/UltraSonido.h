#ifndef UltraSonido_h
#define UltraSonido_h
#include <Arduino.h>
class UltraSonido
{
private:
  int _trigger;
  int _echo;
  int _distancia;
  unsigned long _tiempo;
public:
  UltraSonido(int trigger, int echo);
  int GetDistancia();
};

#endif