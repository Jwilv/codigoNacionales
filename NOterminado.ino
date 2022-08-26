#define DEBUG true
// colocar pines
#define PINRESET 13
#define PIN_PULSADOR 1
#define BUZZER // PONER PIN
#define PULSADOR A3
#define P_MOTOR_R_IZQ 9
#define P_MOTOR_L_IZQ 10
#define P_MOTOR_R_DER 11
#define P_MOTOR_L_DER 12
#define P_ULTRA_DER_TRIGGER 5
#define P_ULTRA_DER_ECHO 4
#define P_ULTRA_IZQ_TRIGGER 6
#define P_ULTRA_IZQ_ECHO 7
#define DISTANCIA_MAX 30
int VELOCIDAD_DE_GIRO = 130;
int VELOCIDAD_RECONOCER = 130;
#define MINIMO_PISO 200
#define NEGROMAX 400
#define CNYDER A5
#define CNYIZQ A4
int VELOCIDAD_ATAQUE = 100; // regular
int VELOCIDAD_SEGUIMIENTO = 145;
////////////////////////////////////
bool giroIzquierda;
bool giroDerecha;
///////////////////////////
int  velocidadSeguidor = 230;

///////////////////////////////////////////////////////////////
String menu = "menu";
String control = "control remoto";
String despejar = "despeja objetos";
String corredor = "seguidor de linea";
enum STATES
{
    INICIO,
    CONTROL,
    DESPEJAR,
    CORREDOR
};
int estadoJugada = INICIO;

////////////////////////////////////////////////

int distanciaDer;
int distanciaIzq;
unsigned long tiempo;
int periodo = 2000;
bool ultraLogicDer = false;
bool ultraLogicIzq = false;
int pisoDer;
int pisoIzq;

////////////pwm motor
int canalDerL = 0;
int canalDerR = 1;
int canalIzql = 2;
int canalIzqR = 3;

int frecuencia = 5000;

int resolucion = 8;
/////////////////////////////////////////////
class Pantalla
{
private:
    int pinReset;

public:
    void Pantalla()
    {
        Adafruit_SSD1306 display(pinReset);
/*Se define una condición para saber si en la librería esta definida la altura de 32 de lo contrario
 *no dejara compilar el código hasta que se cambie la altura correcta desde la librería*/
#if (SSD1306_LCDHEIGHT != 32)
#error("Altura incorrecta, cambie en la librería de Adafruit_SSD1306.h!");
#endif

        void setup()
        {
            /* Se inicia la comunicación I2C en la direcion 0x3C para la pantalla oled 128x32*/
            display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
        }
    }
    /*Se declara la función leer_oled la cual define el tamaño, color, texto y la posición del texto
    que se mostrara en el display oled*/
    void leer_oled(String oracion)
    {
        display.clearDisplay();      // Borra el buffer
        display.setTextSize(1);      // Establece el tamaño de fuente, admite tamaños de 1 a 8
        display.setTextColor(WHITE); // Establece el color
        display.setCursor(35, 10);   // Establecer las coordenadas para mostrar la posición del texto
        display.println(oracion);
    }
};
class Pulsador{
private:
int pin;
public:
Pulsador(int pin){
this->pin = pin;
pinMode(pin,INPUT);
}
 bool getEstado()
  {
    bool estado = digitalRead(pin);
    return estado;
  }
};
/////////////////////////////////////////////////
class MotoresPwm
{
private:
    int _p_r_izq, _p_l_izq, _p_r_der, _p_l_der, _canalDerL, _canalDerR, _canalIzql, _canalIzqR;
    int _frecuencia, _resolucion;

public:
    MotoresPwm(int pr_izq, int pl_izq, int pr_der, int pl_der, int canalDerL, int canalDerR, int canalIzql, int canalIzqR, int frecuencia, int resolucion)
    {
        _p_r_izq = pr_izq;
        _p_l_izq = pl_izq;
        _p_r_der = pr_der;
        _p_l_der = pl_der;
        _canalDerL = canalDerL;
        _canalDerR = canalDerR;
        _canalIzql = canalIzql;
        _canalIzqR = canalIzqR;
        _frecuencia = frecuencia;
        _resolucion = resolucion;

        ledcSetup(_canalDerL, _frecuencia, _resolucion);
        ledcSetup(_canalDerR, _frecuencia, _resolucion);
        ledcSetup(_canalIzql, _frecuencia, _resolucion);
        ledcSetup(_canalIzqR, _frecuencia, _resolucion);

        ledcAttachPin(_p_r_izq, _canalIzqR);
        ledcAttachPin(_p_l_izq, _canalIzql);
        ledcAttachPin(_p_r_der, _canalDerR);
        ledcAttachPin(_p_l_der, _canalDerL);
    }
    void avanzar(int velocidad)
    {

        ledcWrite(_canalIzqR, LOW);
        ledcWrite(_canalIzql, velocidad);

        ledcWrite(_canalDerR, LOW);
        ledcWrite(_canalDerL, velocidad);
    }
    void retroceder(int velocidad)
    {
        ledcWrite(_canalIzqR, velocidad);
        ledcWrite(_canalIzql, LOW);

        ledcWrite(_canalDerR, velocidad);
        ledcWrite(_canalDerL, LOW);
    }
    void frenar()
    {
        ledcWrite(_canalIzqR, LOW);
        ledcWrite(_canalIzql, LOW);

        ledcWrite(_canalDerR, LOW);
        ledcWrite(_canalDerL, LOW);
    }
    void giro_izquierda(int velocidad)
    {
        ledcWrite(_canalIzqR, velocidad);
        ledcWrite(_canalIzql, LOW);

        ledcWrite(_canalDerR, LOW);
        ledcWrite(_canalDerL, velocidad);
    }
    void giro_derecha(int velocidad)
    {
        ledcWrite(_canalIzqR, LOW);
        ledcWrite(_canalIzql, velocidad);

        ledcWrite(_canalDerR, velocidad);
        ledcWrite(_canalDerL, LOW);
    }
    void RotarIzq(int velocidad){
        
        ledcWrite(_canalIzqR, LOW);
        ledcWrite(_canalIzql, velocidad - 20 );

        ledcWrite(_canalDerR, LOW);
        ledcWrite(_canalDerL, velocidad );
    }
    void RotarDer(int velocidad){
        
        ledcWrite(_canalIzqR, LOW);
        ledcWrite(_canalIzql, velocidad  );

        ledcWrite(_canalDerR, LOW);
        ledcWrite(_canalDerL, velocidad - 20);
    }
    void RetrocerGiro(int velocidad){
        ledcWrite(_canalIzqR, velocidad);
        ledcWrite(_canalIzql, LOW);

        ledcWrite(_canalDerR, velocidad - 20);
        ledcWrite(_canalDerL, LOW);

    }
};
//////////////////////////////////////////////////////////////////
class UltraSonido
{
private:
    int _trigger;
    int _echo;
    int _distancia;
    unsigned long _tiempo;

public:
    UltraSonido(int trigger, int echo)
    {
        _trigger = trigger;
        _echo = echo;
        pinMode(_trigger, OUTPUT);
        pinMode(_echo, INPUT);
        digitalWrite(_trigger, LOW);
    }
    int GetDistancia()
    {
        digitalWrite(_trigger, HIGH);
        delayMicroseconds(10);
        digitalWrite(_trigger, LOW);
        _tiempo = pulseIn(_echo, HIGH);
        _distancia = _tiempo / 59;
        return _distancia;
    }
};
class Cny70
{
private:
    int _pin, _receptor;

public:
    Cny70(int pin)
    {
        _pin = pin;
    }

    int GetValor()
    {
        return _receptor = analogRead(_pin);
    }
};
class Buzzer
{
private:
    int _pin;

public:
    Buzzer(int pin)
    {
        _pin = pin;
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

////////////////////////////////////////////////////////////////////////
MotoresPwm *motor = new MotoresPwm(P_MOTOR_R_IZQ, P_MOTOR_L_IZQ, P_MOTOR_R_DER, P_MOTOR_L_DER, canalDerL, canalDerR, canalIzql, canalIzqR, frecuencia, resolucion); // poner pines de los motores como estan en la libreria
UltraSonido *ultraSDer = new UltraSonido(P_ULTRA_DER_TRIGGER, P_ULTRA_DER_ECHO);
UltraSonido *ultraSIzq = new UltraSonido(P_ULTRA_IZQ_TRIGGER, P_ULTRA_IZQ_ECHO);
Cny70 *cnyDer = new Cny70(CNYDER);
Cny70 *cnyIzq = new Cny70(CNYIZQ);
Buzzer *buzzer = new Buzzer(BUZZER);
Pantalla *pantalla = new Pantalla(PINRESET);
Pulsador *pulsador = new Pulsador(PIN_PULSADOR);
/////////////////////////////////////funciones quita objetos ////////////////////
void Adelante(int velocidadAdelante, int velocidadReintegro)
{
    giroIzquierda = (pisoDer < MINIMO_PISO);
    giroDerecha = (pisoIzq < MINIMO_PISO);
    bool atras = (giroDerecha && giroIzquierda);

    if (atras)
        motor->retroceder(velocidadReintegro);
    else if (giroDerecha)
        motor->giro_derecha(velocidadReintegro);
    else if (giroIzquierda)
        motor->giro_izquierda(velocidadReintegro);
    else
        motor->avanzar(velocidadAdelante);
}

// giramos y en caso de no encontrar nada avanzamos
void Reconocer()
{
    motor->giro_izquierda(VELOCIDAD_DE_GIRO); // meter velocidad de giro
    if (millis() < tiempo + periodo)
    {
        tiempo = millis();
        Adelante(VELOCIDAD_RECONOCER, VELOCIDAD_DE_GIRO);
    }
}

void sensores()
{
    distanciaDer = ultraSDer->GetDistancia();
    distanciaIzq = ultraSIzq->GetDistancia();
    pisoDer = cnyDer->GetValor();
    pisoIzq = cnyIzq->GetValor();
    ultraLogicIzq = (distanciaIzq < DISTANCIA_MAX);
    ultraLogicDer = (distanciaDer < DISTANCIA_MAX);
}

void Busquedad()
{
    bool atacar = (ultraLogicIzq && ultraLogicDer);
    bool izquierda = (ultraLogicIzq);
    bool derecha = (ultraLogicDer);

    if (atacar)
        Adelante(VELOCIDAD_ATAQUE, VELOCIDAD_DE_GIRO);
    else if (izquierda)
        motor->giro_izquierda(VELOCIDAD_SEGUIMIENTO);
    else if (derecha)
        motor->giro_derecha(VELOCIDAD_SEGUIMIENTO);
    else
        Reconocer();
}
//////////////////////////////////////cambiar de modo////////////////
void touch()
{
}
//////////////////////////////////////////////seguidor de linea//////////////
// llamar  a sensores
void seguir()
{
    pisoDer = cnyDer->GetValor();
    pisoIzq = cnyIzq->GetValor();
    bool atras = (NEGROMAX < pisoDer) || (NEGROMAX < pisoIzq);
    if(NEGROMAX < pisoDer){
        motor->RotarIzq(velocidadSeguidor);
    }
    if(NEGROMAX < pisoIzq){
        motor->RotarDer(velocidadSeguidor);
    }
    if(atras){
        motor->RetrocerGiro(velocidadSeguidor);
    }
    else motor->avanzar(velocidadSeguidor);
}
/////////////////////////////////////
void setup(){

}

///////////////////////////////////////////////////////////////////
void loop()
{
    switch (estadoJugada)
    {
    case 0:
    {
        pantalla->leer_oled(menu);
        sensores();
        Busquedad();
        // poner inicio
        break;
    }
    case 1:
    {
        pantalla->leer_oled(control);

        break;
    }
    case 2:
    {
        pantalla->leer_oled(despejar);

        break;
    }
    case 3:
    {
        pantalla->leer_oled(corredor);

        break;
    }
    }
}
