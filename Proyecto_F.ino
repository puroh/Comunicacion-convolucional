
#include "comunicacion.h"

comunicacion x;
void setup()
{
    pinMode(A0,INPUT);
    pinMode(8,OUTPUT);
    Serial.begin(9600);
}


void loop()
{
	uint32_t dato=1234,recep;

      x.modular(dato);//pin digital 8
    
    
      recep=x.demodular();  
      
}
