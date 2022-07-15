#define DEGUG 1
//definimos los valores maximos minimos... etc para utilizar dentro del algoritmo 
#define MAXIMO 1000
#define MINIMO 100
#define INTERMEDIO 400
#define SENSOR1 = xx; //indicar los pines 
//cuchame para que funque tenes que poner que el sensor 1 sea el izquierdo visto desde arriba y el robot viendo para adelante
//asi hasta el 5 que tiene que ser el de la derecha del todo,pone los en ese orden 
#define SENSOR2 = xx;
#define SENSOR3 = xx;
#define SENSOR4 = xx;
#define SENSOR5 = xx;
int recep1 ; //variable para el almacenamiento de los datos recolectados por los sensores estos coresponde de la siguiente manera
// SENSOR1-->recep1
int recep2 ;
int recep3 ;
int recep4 ;
int recep5 ;
class Motor{

}

void recepcion(){
    recep1 = analogRead(SENSOR1);
    recep2 = analogRead(SENSOR2);
    recep3 = analogRead(SENSOR3);
    recep4 = analogRead(SENSOR4);
    recep5 = analogRead(SENSOR5);
}
void acciones(){
    recepcion();
    bool adelante = (recep1 <= MINIMO && recep2 <= MINIMO ) 
    if
}
void setup(){
    Serial.begin(9600);
}
void loop(){
    
 if(DEGUG){
    Serial.print("recep1//");
    Serial.println(recep1);
    Serial.print("recep2//");
    Serial.println(recep2);
    Serial.print("recep3//");
    Serial.println(recep3);
    Serial.print("recep4//");
    Serial.println(recep4);
    Serial.print("recep5//");
    Serial.println(recep5);
    }
}
