#include <Arduino.h>
#include "Motores.h"
#include "UltraSonido.h"
#include"Buzzer.h"
#include "Switch.h"

#define DEBUG false

// motores

#define MOTOR_IZQUIERDO_R_PWM 9
#define MOTOR_IZQUIERDO_L_PWM 10

#define MOTOR_DERECHO_R_PWM 11
#define MOTOR_DERECHO_L_PWM 12

// pulsadores
#define PULSADOR A6
#define DIP_SWITCH 3

// senores ultrasonido

#define SENSOR_US_IZQUIERDO_TRIGGER 7
#define SENSOR_US_IZQUIERDO_ECHO 6

#define SENSOR_US_DERECHO_TRIGGER 5
#define SENSOR_US_DERECHO_ECHO 4

// sensores infrarojos

#define SENSOR_INFRAROJO_IZQUIERDO A4
#define SENSOR_INFRAROJO_DERECHO A5

// buzzer

#define BUZZER 2

Motores *ruedas = new Motores(MOTOR_IZQUIERDO_R_PWM, MOTOR_IZQUIERDO_L_PWM, MOTOR_DERECHO_R_PWM, MOTOR_DERECHO_L_PWM);

Switch *pulsador = new Switch(PULSADOR);

UltraSonido *ultrasonido_izquierdo = new UltraSonido(SENSOR_US_IZQUIERDO_TRIGGER, SENSOR_US_IZQUIERDO_ECHO);
UltraSonido *ultrasonido_derecho = new UltraSonido(SENSOR_US_DERECHO_TRIGGER, SENSOR_US_DERECHO_ECHO);

Buzzer *buzzer = new Buzzer(BUZZER);

Switch *Infrarojo_izquierdo = new Switch(SENSOR_INFRAROJO_IZQUIERDO);
Switch *Infrarojo_derecho = new Switch(SENSOR_INFRAROJO_DERECHO);

Switch *switch_estrategias = new Switch(DIP_SWITCH);

void Estrategia_Fon()
{
}

void Estrategia_Abril()
{
}

void setup()
{
  if (DEBUG) Serial.begin(9600);
}

void loop()
{
  switch_estrategias->getEstado() ? Estrategia_Fon() : Estrategia_Abril(); // Intercambiar estrategias
}