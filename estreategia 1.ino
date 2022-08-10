///////////////////////EL COSO QUE LIMPIA EL COSO Y HACE COSAS ////////////////////////////////////////////
// QUITA OBJETOS////

#include <Arduino.h>
#include <Motores.h>
#include <UltraSonido.h>
#include <Buzzer.h>
#include <Cny70.h>

#define P_ULTRA_DER_TRIGGER 1
#define P_ULTRA_DER_ECHO 1
#define P_ULTRA_IZQ_TRIGGER 1
#define P_ULTRA_IZQ_ECHO 1
#define DEBUG true
#define BUZZER // poner pin
#define DISTANCIA_MAX 350
int VELOCIDAD_DE_GIRO = 130;
#define MINIMO_PISO 200;
int VELOCIDAD_ATAQUE = 200;
int distanciaDer;
int distanciaIzq;
unsigned long tiempo;
int periodo;

Motores *motor = new Motores(1, 2, 3, 4); // poner pines de los motores como estan en la libreria
UltraSonido *ultraSDer = new UltraSonido(P_ULTRA_DER_TRIGGER, P_ULTRA_DER_ECHO);
UltraSonido *ultraSIzq = new UltraSonido(P_ULTRA_IZQ_TRIGGER, P_ULTRA_IZQ_ECHO);




// giramos y en caso de no encontrar nada avanzamos 
void Reconocer()
{
    motor->giro_izquierda(123); // meter velocidad de giro
    if (millis() < tiempo + periodo)
    {
        tiempo = millis();
        Adelante();
    }
}

// obtenemos la distancia de los sensores
// de los ultra sonido derecho y izquierdo
// y guardamos el valor en variables globales
void sensores()
{
    distanciaDer = ultraSDer->GetDistancia();
    distanciaIzq = ultraSIzq->GetDistancia();
}

//avanzamos solo si no estamos sobre la linea del borde en ese caso doblamos 
// poner parametros en limite 
void Adelante(int velocidadAtaque,int velocidadAtaque)
{
    bool limite; 
    if (limite)
        motor->avanzar(velocidadAtaque);
    else
        motor->giro_derecha(velocidadAtaque);
}


//vamos a identificar si hay algo antes sel limite maximo 
//y si lo hay atacamos
//poniendo las velocidades  
void Busquedad()
{
    bool objeto = (distanciaDer < DISTANCIA_MAX) || (distanciaIzq < DISTANCIA_MAX);
    if (objeto)
        Adelante();
    else
        Reconocer();
}

void setup()
{
    Serial.begin(9600);
}

void loop()
{
    void Busquedad();
}
