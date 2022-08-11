#include <Arduino.h>
#include "UltraSonido.h"

UltraSonido::UltraSonido(int trigger, int echo)
{
  _trigger = trigger;
  _echo = echo;
  pinMode(_trigger, OUTPUT);
  pinMode(_echo, INPUT);
  digitalWrite(_trigger, LOW);
}
int UltraSonido::GetDistancia()
{
  digitalWrite(_trigger, HIGH);
  delayMicroseconds(4);
  digitalWrite(_trigger, LOW);
  _tiempo = pulseIn(_echo, HIGH); // obtenemos el ancho del pulso
  _distancia = _tiempo / 59;      // escalamos el tiempo a una distancia en cm
  return _distancia;
}
