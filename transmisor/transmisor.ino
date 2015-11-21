#include "comunicacion.h"
#include <avr/io.h>
#include <avr/interrupt.h>


int estado=1;
int Salida=12;
int i=0,j=0,m=0,n=0,p=0;
uint32_t codificado;

comunicacion x;

void setup() {
  Serial.begin(9600);
  pinMode(Salida,OUTPUT);
  pinMode(A0,INPUT);
  cli();
  TCCR1A=0;
  TCCR1B=0;
  OCR1A=4999;//Para 20ms
  TCCR1B|=(1<<WGM12);
  TCCR1B|=(1<<CS11);
  TCCR1B|=(1<<CS10);
  TIMSK1|=(1<<OCIE1A);
  sei();
}

void loop(){
  
  if (p!=1){
  int sensorValue = analogRead(A0);
  // corvierte la lectura analoga (con una lectura analoga de 0 - 1023) a el valor de la temperatura en grados celcius:
  uint8_t temp = (100.0 * sensorValue * 4.84) / 1023;
  Serial.println(temp-1,BIN);
  codificado=x.codificar((temp-1));
    p=1;  
    }
  
}

  ISR(TIMER1_COMPA_vect){
        if(i!=600){
            digitalWrite(Salida,estado);
            i++;
            if((i==600)&(j!=1)){estado=!estado;i=599;j=1;}
        }
        else{
            if(n!=1){
                digitalWrite(Salida,((codificado>>m)&1));
                Serial.print("Dato enviado\n");
                Serial.println(m);
                Serial.println((codificado>>m)&1);
                m++;
                if((m==32)&(n!=1)){n=1;}  
            }
            else{
                  i=0;j=0;m=0;n=0;
                  estado=1;
                  p=0;
            }
      
        }
            
}
