#include <Arduino.h>
#include "Cny70.h"

Cny70::Cny70(int pin){
_pin = pin;
}

int Cny70::GetValor(){
    return _receptor = analogRead(_pin);
}