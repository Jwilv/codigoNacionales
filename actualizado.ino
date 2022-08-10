

//////////////////////////////////////estrategia 1///////////////////////

#include <Arduino.h>
#include <Motores.h>
#include <UltraSonido.h>
#include <Buzzer.h>
#include <Cny70.h>


//colocar pines
#define P_ULTRA_DER_TRIGGER 1
#define P_ULTRA_DER_ECHO 1
#define P_ULTRA_IZQ_TRIGGER 1
#define P_ULTRA_IZQ_ECHO 1
#define DEBUG true
#define BUZZER // poner pin
#define DISTANCIA_MAX 200
int VELOCIDAD_DE_GIRO = 130;
int VELOCIDAD_RECONOCER = 130;
#define MINIMO_PISO 200
#define CNYDER 1
#define CNYIZQ 1
int VELOCIDAD_ATAQUE = 200;


int distanciaDer;
int distanciaIzq;
int pisoDer;
int pisoIzq;
unsigned long tiempo;
int periodo;

Motores *motor = new Motores(1, 2, 3, 4); // poner pines de los motores como estan en la libreria
UltraSonido *ultraSDer = new UltraSonido(P_ULTRA_DER_TRIGGER, P_ULTRA_DER_ECHO);
UltraSonido *ultraSIzq = new UltraSonido(P_ULTRA_IZQ_TRIGGER, P_ULTRA_IZQ_ECHO);
Cny70 *cnyDer = new Cny70(CNYDER);
Cny70 *cnyIzq = new Cny70(CNYIZQ);



// giramos y en caso de no encontrar nada avanzamos 
void Reconocer()
{
    motor->giro_izquierda(VELOCIDAD_DE_GIRO); // meter velocidad de giro
    if (millis() < tiempo + periodo)
    {
        tiempo = millis();
        Adelante(VELOCIDAD_RECONOCER,VELOCIDAD_DE_GIRO);
    }
}

// obtenemos la distancia de los sensores
// de los ultra sonido derecho y izquierdo
// y guardamos el valor en variables globales
void sensores()
{
    distanciaDer = ultraSDer->GetDistancia();
    distanciaIzq = ultraSIzq->GetDistancia();
    pisoDer = cnyDer->GetValor();
    pisoIzq = cnyIzq->GetValor();
}

//avanzamos solo si no estamos sobre la linea del borde en ese caso doblamos 
// poner parametros en limite 
//la velocidad de reintegro es la velocidad de giro para volver a entrar en la pista 
void Adelante(int velocidadAdelante,int velocidadReintegro)
{
    bool limite  = true; 
    if (limite)
        motor->avanzar(velocidadAdelante);
    else
        motor->giro_derecha(velocidadReintegro);
}


//vamos a identificar si hay algo antes sel limite maximo 
//y si lo hay atacamos
//poniendo las velocidades  
void Busquedad()
{
    bool objeto = (distanciaDer < DISTANCIA_MAX) || (distanciaIzq < DISTANCIA_MAX);
    if (objeto)
        Adelante(VELOCIDAD_ATAQUE,VELOCIDAD_DE_GIRO);
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
