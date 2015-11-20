/*
  ReadAnalogVoltage
  Reads an analog input on pin 0, converts it to voltage, and prints the result to the serial monitor.
  Attach the center pin of a potentiometer to pin A0, and the outside pins to +5V and ground.
 
 This example code is in the public domain.
 
  El circuito:
  
  Entrada analoga
  A0 entrada analoga del sensor
  
  LCD:
 * LCD RS pin to digital pin 51
 * LCD Enable pin to digital pin 47
 * LCD D4 pin to digital pin 43
 * LCD D5 pin to digital pin 39
 * LCD D6 pin to digital pin 35
 * LCD D7 pin to digital pin 31
 * LCD R/W pin to tierra
 * VO --> 10K potenciometro:
 * vss --> tierra
 * VDD --> 5v
 * wiper(limpiaparabrisas) to LCD VO pin (pin 3)
 */
 
#include <LiquidCrystal.h>


LiquidCrystal lcd(51, 47, 43, 39, 35 , 31);
 
// the setup routine runs once when you press reset:
void setup() {
  // inicia la comunicacion serial a 9600 bits por segundo:
  Serial.begin(9600);
  lcd.begin(16, 2);
  lcd.setCursor(0,1);
  
}

// the loop routine runs over and over again forever:
void loop() {
  // lee la lectura analoga del pin 0:
  int sensorValue = analogRead(A0);
  // corvierte la lectura analoga (con una lectura analoga de 0 - 1023) a el valor de la temperatura en grados celcius:
  float temp = (100.0 * sensorValue * 4.84) / 1023.0;
  // imprime el valor leido de temperatura en el puerto serial:
  Serial.println(temp);
  // Imprime el valor leido de temperatura en la lcd:
  lcd.setCursor(1,0);//posiciona cursor
  lcd.write("Temp: ");//muestra en la lcd
  lcd.setCursor(1,1);
  lcd.print(temp);
  lcd.print(" *C");
  delay(1000);
}
