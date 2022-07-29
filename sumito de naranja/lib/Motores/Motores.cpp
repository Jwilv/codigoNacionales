#include <Arduino.h>
#include "Motores.h"
Motores:: Motores(int pr_izq, int pl_izq, int pr_der, int pl_der)
  {
    _p_r_izq = pr_izq;
    _p_l_izq = pl_izq;
    _p_r_der = pr_der;
    _p_l_der = pl_der;

    pinMode(_p_r_izq, OUTPUT);
    pinMode(_p_l_izq, OUTPUT);
    pinMode(_p_r_der, OUTPUT);
    pinMode(_p_l_der, OUTPUT);
  }
  void Motores:: avanzar(int velocidad)
  {
    digitalWrite(_p_r_izq, LOW);
    analogWrite(_p_l_izq, velocidad);

    digitalWrite(_p_r_der, LOW);
    analogWrite(_p_l_der, velocidad);
  }
   void Motores:: retroceder(int velocidad)
  {
    digitalWrite(_p_l_izq, LOW);
    analogWrite(_p_r_izq, velocidad);

    digitalWrite(_p_l_der, LOW);
    analogWrite(_p_r_der, velocidad);
  }
   void Motores:: frenar()
  {
    digitalWrite(_p_r_izq, LOW);
    digitalWrite(_p_l_izq, LOW);

    digitalWrite(_p_r_der, LOW);
    digitalWrite(_p_l_der, LOW);
  }
  void Motores:: giro_izquierda(int velocidad)
  {
    digitalWrite(_p_l_izq, LOW);
    analogWrite(_p_r_izq, velocidad);

    digitalWrite(_p_r_der, LOW);
    analogWrite(_p_l_der, velocidad);
  }
  void Motores:: giro_derecha(int velocidad)
    {
        digitalWrite(_p_r_izq, LOW);
        analogWrite(_p_l_izq, velocidad);

        digitalWrite(_p_l_der, LOW);
        analogWrite(_p_r_der, velocidad);
    }