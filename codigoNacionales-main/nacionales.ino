///añadir librerias 


// valor max de los ultra sonidos 
#define ULTRAMAX 380,

//logica 
bool encontrado = false;
unsigned long tiempo;
int periodo = 2000;

#define VELOCIDADESTRATEGIA1 HIGH

int derecha,izquierda;

void buscar(){
    //va a dar vueltas hasta que encuentre
    // a un objetivo en caso de no encontrar va a ir durate un periodo de tiempo hacia adelante

    //giroDerecha(velocidadBusquedad)
     
    if(millis()<tiempo + periodo){
        tiempo = millis();
     Avanzar();
    }
}

bool Infrarojos(){
    //obtener valores y retornar un valor 
}


void Avanzar(int velocidad){
Infrarojos();
if(negro){
    //motores adelante 
}else GiroDerecha();
}


void detectar(){
//obtenemos los valores de los ultra sonidos con las librerias

derecha,izquierda;//vamos a guardar los valores en estas variables globales 

}

void estrategia1(){
    detectar();

    if(encontrado){
        Avanzar();
    }
    else buscar();
}
