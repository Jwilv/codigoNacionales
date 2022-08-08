void Motores(int pr_izq, int pl_izq, int pr_der, int pl_der)
  {

    pinMode(pr_izq, OUTPUT);
    pinMode(pl_izq, OUTPUT);
    pinMode(pr_der, OUTPUT);
    pinMode(pl_der, OUTPUT);
  }
  
void setup(){
  Motores();
}
  void avanzar(int velocidad)
  {
    digitalWrite(pr_izq, LOW);
    analogWrite(pl_izq, velocidad);

    digitalWrite(pr_der, LOW);
    analogWrite(pl_der, velocidad);
  }
  void loop(){
    avanzar(255);
  }
