
#include "comunicacion.h"

uint8_t dato=255;
uint32_t codificado;

comunicacion x;
void setup()
{
    pinMode(12,OUTPUT);
    pinMode(13,OUTPUT);
    Serial.begin(9600);
}


void loop()
{
    codificado=x.codificar(dato);
    Serial.print("El numero total es: ");
    Serial.print(codificado,BIN);
    Serial.print("\n");
    digitalWrite(12,LOW);
    x.modular(codificado);
    //Serial.println("Entro");
         
}

