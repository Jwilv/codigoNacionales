     ////////////////////////////  CONTROL REMOTO /////////////////////////////////////////

#define DEBUG true

#define PRIMERA_MARCHA 1
#define SEGUNDA_MARCHA 2

#define P_MOTOR_R_IZQ 15
#define P_MOTOR_L_IZQ 2
#define P_MOTOR_R_DER 4
#define P_MOTOR_L_DER 16

#define PIN_BUZZER 1

#define PIN_PULSADOR 1

#define DEAD_ZONE_IZQUIERDA -30
#define DEAD_ZONE_DERECHA 30

#define VELOCIDAD_ESTANDAR 220
#define VELOCIDAD_ENBESTIDA 255

enum{
    CAMBIARMARCHA,
    FRENODEMANO,
    AVANZAR,
    RETROCESO,
    DOBLARDERECHA,
    DOBLARIZQUIERDA
};

int estadoControl = FRENODEMANO;

int marcha ;

bool esperandoPulsador = true;


bool doblarDerecha  ;
bool doblarizquierda ;
bool avanzar ; 
bool Retroceso ;
bool cambioDeMarcha ; 
bool frenoDeMano;

int velocidad;

////////////pwm motor
int canal_l_derecho = 0;
int canal_r_derecho = 1;
int canal_l_izquierdo = 2;
int canal_r_izquierdo = 3;

int frecuencia = 5000;

int resolucion = 8;

class MotoresPwm
{
private:
    int pin_r, pin_l,canal_r, canal_l,frecuencia,resolucion;
public:
    MotoresPwm(int pin_r, int pin_l, int canal_l, int canal_r,int frecuencia, int resolucion)
    {
        this->pin_r = pin_r;
        this->pin_l= pin_l;
        this->canal_r= canal_r;
        this->canal_l = canal_l;
        this->frecuencia = frecuencia;
        this->resolucion = resolucion;


        ledcSetup(canal_l,frecuencia,_resolucion);
        ledcSetup(canal_r,frecuencia,_resolucion);
        ledcAttachPin(pin_r,canal_r_izquierdo);
        ledcAttachPin(pin_l,canal_l_izquierdo);
    }
    void avanzar(int velocidad)
    {
       
        ledcWrite(canal_r_izquierdo, LOW);
        ledcWrite(canal_l_izquierdo,velocidad);
    }
    void retroceder(int velocidad)
    {
       ledcWrite(canal_r_izquierdo, velocidad);
        ledcWrite(canal_l_izquierdo, LOW);
    }
    void frenar()
    {
        ledcWrite(canal_r_izquierdo, LOW);
        ledcWrite(canal_l_izquierdo, LOW);
    }
};
class Buzzer
{
private:
    int pin;

public:
    Buzzer(int pin)
    {
         this->pin = pin;
        pinMode(pin, OUTPUT);
    }
    void Encender()
    {
        digitalWrite(_pin, HIGH);
    }
    void Apagar()
    {
        digitalWrite(_pin, LOW);
    }
};

class Pulsador
{
 private:
 int pin;
 public:
 Pulsador(int pin){
 this->pin = pin;
 pinMode(pin,INPUT);
 }

 bool getEstado(){
    bool estado = digitalRead(pin);
    return estado;
  }
};

class Movimientos(){
private:
 int pin_r_izquierdo, pin_l_izquierdo, pin_r_derecho, pin_l_derecho, canal_l_derecho, canal_r_derecho, canal_l_izquierdo, canal_r_izquierdo;
    int frecuencia,resolucion;
    public:
    Movimientos(int pin_r_izquierdo, int pin_l_izquierdo, int pin_r_derecho, int pin_l_derecho, int canal_l_derecho, int canal_r_derecho, int canal_l_izquierdo, int canal_r_izquierdo, int frecuencia, int resolucion){
        this->pin_r_izquierdo = pin_r_izquierdo;
        this->pin_l_izquierdo = pin_l_izquierdo;
        this->pin_r_derecho = pin_r_derecho;
        this->pin_l_derecho = pin_l_derecho;
        this->canal_l_derecho = canal_l_derecho;
        this->canal_r_derecho = canal_r_derecho;
        this-> canal_l_izquierdo = canal_l_izquierdo;
        this->canal_r_izquierdo = canal_r_izquierdo;
        this->frecuencia = frecuencia;
        this->resolucion = resolucion;

        MotoresPwm *motorDerecho = new MotoresPwm(pin_r_derecho, pin_l_izquierdo,canal_l_derecho,canal_r_derecho,frecuencia,resolucion);
        MotoresPwm *motorIzquierdo= new MotoresPwm(pin_r_izquierdo, pin_l_izquierdo,canal_l_izquierdo,canal_r_izquierdo,frecuencia,resolucion);
    }
    void Avanzar(velocidad){
        motorDerecho->avanzar(velocidad);
        motorIzquierdo->avanzar(velocidad);
    }
    void Retroceder(velocidad){
        motorDerecho->retroceder(velocidad);
        motorIzquierdo->retroceder(velocidad);
    }
    void DoblarDerecha(velocidad){
         motorDerecho->retroceder(velocidad);
        motorIzquierdo->avanzar(velocidad);
    }
    void DoblarIzquierda(velocidad){
        motorDerecho->avanzar(velocidad);
        motorIzquierdo->retroceder(velocidad);retroceder

    }
    void Freno(){
       motorDerecho->frenar();
       motorIzquierdo->frenar();
    }

};

Movimientos *movimientos = new Movimientos(P_MOTOR_R_IZQ, P_MOTOR_L_IZQ, P_MOTOR_R_DER, P_MOTOR_L_DER, canal_l_derecho, canal_r_derecho, canal_l_izquierdo, canal_r_izquierdo, frecuencia, resolucion);

Buzzer *buzzer =new Buzzer(PIN_BUZZER);

Pulsador *pulsador = new Pulsador(PIN_PULSADOR);


void Inicio(){

    while(esperandoPulsador){
    bool inicio = pulsador->getEstado;
    if(inicio){
        buzzer->Encender();
        delay(5000);
        esperandoPulsador = false ;
        Buzzer->Apagar();
    }
    }
    
}

void CambiarMarchas(){
 marcha++;
 if(marcha == PRIMERA_MARCHA) velocidad = VELOCIDAD_ESTANDAR;
 if(marcha == SEGUNDA_MARCHA) velocidad = VELOCIDAD_ENBESTIDA;
 if (marcha > SEGUNDA_MARCHA) marcha = PRIMERA_MARCHA
}


void ControlRemoto(){
    doblarDerecha = PS4.LStickX() > DEAD_ZONE_DERECHA;
    doblarizquierda = PS4.LStickX()  <  DEAD_ZONE_IZQUIERDA;
    avanzar = PS4.R2(); 
    Retroceso = PS4.L2() ;
    cambioDeMarcha = PS4.Circle(); 
    frenoDeMano = PS4.L1(); 

    if(cambioDeMarcha) estadoControl = CAMBIARMARCHA;
    if(frenoDeMano) estadoControl = FRENODEMANO;
    if(avanzar) estadoControl = AVANZAR;
    if (Retroceso) estadoControl = RETROCESO;
    if(doblarDerecha) estadoControl = DOBLARDERECHA;
    if(doblarizquierda) estadoControl = DOBLARIZQUIERDA;
    else estadoControl = FRENODEMANO;
}

void setup(){
PS4.begin();
Inicio();
CambiarMarchas();
}

void loop{
    ControlRemoto();
}

void Controles(){
    switch(){
        case CAMBIARMARCHA:
        {   
            CambiarMarchas();
            ControlRemoto();
            break;
        }
        case FRENODEMANO:
        {
            movimientos->Freno();
            ControlRemoto();

            break;
        }
        case AVANZAR:
        {
            movimientos->Avanzar(velocidad);
            ControlRemoto();

            break;
        }
        case RETROCESO:
        {
            movimientos->Retroceder(velocidad);
            ControlRemoto();

            break;
        }
        case DOBLARDERECHA:
        {   
            movimientos->DoblarDerecha(velocidad);
            ControlRemoto();

            break;
        }
        case DOBLARIZQUIERDA:
        {
            movimientos->DoblarIzquierda(velocidad);
            ControlRemoto();
            
            break;
        }
    }
}
