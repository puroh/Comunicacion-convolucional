#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdint.h>
#include <LiquidCrystal.h>
#include "comunicacion.h"

LiquidCrystal lcd(31, 35, 39, 43, 47 , 51);
int actual=1,anterior=1,i=0,parimpar=0,n=0;
int Entrada=8;
int bin;
uint16_t dato1=0,dato2=0;
uint32_t total=0x00000000;
uint8_t decodificado;

comunicacion x;

void setup() {
  pinMode(Entrada,INPUT);
  Serial.begin(9600);
  lcd.begin(16, 2);
  lcd.setCursor(0,1);
  cli();
  TCCR1A=0;
  TCCR1B=0;
  TCCR1B|=(1<<CS10); 
  TIMSK1|=(1<<TOIE1);
  sei();
}
void loop(){
}

ISR(TIMER1_OVF_vect){
   
    actual=digitalRead(Entrada);
    if(anterior==(!actual)){
                                cli();
                                TCCR1A=0;
                                TCCR1B=0;
                                OCR1A=2499;//Para 20ms
                                
                                TCCR1B|=(1<<WGM12);
                                TCCR1B|=(1<<CS11);
                                TCCR1B|=(1<<CS10);
                                
                                TIMSK1|=(1<<OCIE1A);
                                sei();
    
    
    }
    anterior=actual;
    
}

ISR(TIMER1_COMPA_vect){
    if((parimpar%2)==1){
//     Serial.print("Valor de i:\n");
//     Serial.println(i);
     //bin=(digitalRead(Entrada));//Serial.println(digitalRead(Entrada));
     if(i>=0&i<16){
     dato1|=(digitalRead(Entrada)<<i);}
     if(i>=16&i<=31){
     dato2|=(digitalRead(Entrada)<<(i-16));
     }
 
    
     i++;
     }
      parimpar++;
    if(i==32){
          cli();
          Serial.print("Dato 1\n");
          Serial.println(dato1>>1,BIN);
          Serial.print("Dato 2\n");
          Serial.println(dato2<<1,BIN);
          total|=(dato1>>1);
          total|=((dato2<<1)<<14);
      
         
         
          decodificado=x.decodificar(total);
          decodificado=decodificado;
          Serial.println(decodificado,BIN);
          
          if(n!=1){
          lcd.setCursor(1,0);//posiciona cursor
          lcd.write("Temperatura: ");//muestra en la lcd
          lcd.setCursor(1,1);
          lcd.print(decodificado);
          delay(2000);
          n=1;
          }
          actual=1;anterior=1;i=0;
          parimpar=0;
          TCCR1A=0;
          TCCR1B=0;
          TCCR1B|=(1<<CS10); 
          TIMSK1|=(1<<TOIE1);
          sei();
  
    }

}


