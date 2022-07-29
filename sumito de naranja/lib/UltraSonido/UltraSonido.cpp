#include <Arduino.h>
#include "UltraSonido.h"

UltraSonido::UltraSonido(int trigger, int echo)
  {
    _trigger = trigger;
    _echo = echo;
    pinMode(pin_trigger, OUTPUT);
    pinMode(pin_echo, INPUT);
    digitalWrite(pin_trigger, LOW);
  }
  int GetDistancia()
  {digitalWrite(pin_trigger, HIGH);
    digitalWrite(pin_trigger, LOW);
    tiempo = pulseIn(pin_echo, HIGH); // obtenemos el ancho del pulso
    distancia = tiempo / 59;          // escalamos el tiempo a una distancia en cm
    return distancia;
  }

  int UltraSonido :: GetDistancia()
  {digitalWrite(pin_trigger, HIGH);
    digitalWrite(pin_trigger, LOW);
    tiempo = pulseIn(pin_echo, HIGH); // obtenemos el ancho del pulso
    distancia = tiempo / 59;          // escalamos el tiempo a una distancia en cm
    return distancia;
  }
