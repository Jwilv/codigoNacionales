#define DEGUG 1
int sensorDer = xx;
int sensorIzq = xx;
int recepDer = xx;
int recepIzq = xx;
void setup(){
    Serial.begin(9600);
}
void loop(){
recepDer = digitalRead(sensorDer);
recepIzq = digitalRead(sensorIzq);
 if(DEGUG){
    Serial.print("sensor derecho");
    Serial.println(recepDer);
    Serial.print("sensor izquierod");
    Serial.println(recepIzq);
    }
}
