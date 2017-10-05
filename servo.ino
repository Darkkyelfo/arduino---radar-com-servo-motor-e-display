#include <Servo.h>
#include <Ultrasonic.h>
#include "Wire.h"
#include "Adafruit_LiquidCrystal.h"

#define SERVO 6 // Porta Digital 6 PWM
#define BUZZER 9
#define LIMITE 70
#define anguloFinal 180
#define espacos 45
#define tempoParado 2000

Servo s; // Variável Servo
int pos; // Posição Servo
float distancia;

Ultrasonic ultrasonic(10, 13);
Adafruit_LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

void pegarDistancia(int pos){
    digitalWrite(BUZZER,LOW);
    s.write(pos);
    delay(500);
    distancia = ultrasonic.distanceRead();
    Serial.print("Distancia em CM: ");
    Serial.println(distancia);
    lcd.setCursor(11, 0);
    lcd.print(distancia);
    if(distancia < LIMITE){
      digitalWrite(BUZZER,HIGH);
    }
    delay(tempoParado);
  }
void setup ()
{
  pinMode(BUZZER, OUTPUT);
  lcd.begin(16, 2);
  lcd.print("Distancia: ");
  Serial.begin(9600);
  s.attach(SERVO);
  s.write(0); // Inicia motor posição zero
}
 
void loop()
{
  // Pass INC as a parameter to get the distance in inches
  for(pos = 0; pos <= anguloFinal; pos = pos + espacos)
  {
    pegarDistancia(pos);
  }
/*delay(1000);*/
  for(pos = anguloFinal - espacos; pos >= espacos; pos = pos - espacos)
  {
    pegarDistancia(pos);
  }
}
