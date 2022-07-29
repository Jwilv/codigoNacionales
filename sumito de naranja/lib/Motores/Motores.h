#ifndef Motores_h
#define Motores_h
#include <Arduino.h>
class Motores
{
private:
    int _p_r_izq, _p_l_izq, _p_r_der, _p_l_der;
    int _velocidad;

public:
    Motores(int pr_izq, int pl_izq, int pr_der, int pl_der);
    void avanzar(int velocidad);
    void retroceder(int velocidad);
    void frenar();
    void giro_izquierda(int velocidad);
    void giro_derecha(int velocidad);
};
#endif