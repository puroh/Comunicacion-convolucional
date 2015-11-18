#include <Event.h>
#include <Timer.h>
#include "comunicacion.h"

uint32_t codificado;
 uint8_t decodificado;
comunicacion x;
int j=31;

void setup()
{
    pinMode(12,INPUT);
    pinMode(13,INPUT);
    attachInterrupt(0,blink,RISING);
    Serial.begin(9600);
}


void loop()
{
//Serial.println(analogRead(A0));
 
}
void blink(){
    
            
            codificado|=(digitalRead(12))<<j;
            Serial.print("Dato Leido: ");
            Serial.println(codificado);
            Serial.println(j);
           j--;
          if(j==0){
               j=31;
           decodificado=x.decodificar(codificado);
           Serial.print("Dato decodificado:\n");
           Serial.println(decodificado);
           codificado=0;  
           } 
}
