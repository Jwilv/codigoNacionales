#ifndef Cny70_h
#define Cny70_h 
#include <Arduino.h>

class Cny70
{
private:
int _pin,_receptor;

public:

Cny70(int pin);
int GetValor();


};

#endif