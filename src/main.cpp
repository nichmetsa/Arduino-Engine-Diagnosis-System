#include <Arduino.h>
#include <Wire.h>
#include <max6675.h>
#include <SPI.h>
//OIL TERMOPAR PINS
const byte thermoDOoleo = 8;  //VERDE/GREEN-SD
const byte thermoCSoleo = 7;  //AMARELO/YELLOW-CS
const byte thermoCLKoleo = 6; //LARANJA/ORANGE-SCK
//CYLINDER HEAD TERMOPAR PINS
const byte thermoDOcab = 11;  //AZUL/BLUE-SD
const byte thermoCScab = 10;  //ROXO/PURPLE-CS
const byte thermoCLKcab = 9; //CINZA/GREY-SCK
//LED PINS
const byte ledG = 3; //GREEN
const byte ledY = 4; //YELLOW
const byte ledR = 5; //RED
//Termopar SETUP
MAX6675 thermocoupleoleo(thermoCLKoleo, thermoCSoleo, thermoDOoleo);
MAX6675 thermocouplecab(thermoCLKcab, thermoCScab, thermoDOcab);
//temp OIL
const byte topTEMPoleo = 80;
const byte maxTEMPoleo = 100;
//temp CYLINDER HEAD
const byte topTEMPcab = 160;
const byte maxTEMPcab = 200;

void setup()
{
  Serial.begin(9600);
  pinMode(ledR, OUTPUT);
  pinMode(ledG, OUTPUT);
  pinMode(ledY, OUTPUT);
  pinMode(12, OUTPUT);
  //TO SHOW THAT ALL LEDS ARE WORKING
  digitalWrite(ledR, HIGH);
  digitalWrite(ledG, HIGH);
  digitalWrite(ledY, HIGH);
  delay(1500);
}
void loop()
{
  digitalWrite(12, HIGH); //USING PIN 12 AS 5V SOURCE FOR MY TERMPOPAR
  float temperaturaoleo = thermocoupleoleo.readCelsius();;
  float temperaturacab = thermocouplecab.readCelsius();;
  Serial.print("oil = ");
  Serial.println(temperaturaoleo);
  Serial.print("cylinder head = ");
  Serial.println(temperaturacab);

  if (temperaturaoleo > maxTEMPoleo || temperaturacab > maxTEMPcab)
  {
    digitalWrite(ledR, HIGH);
    digitalWrite(ledG, LOW);
    digitalWrite(ledY, LOW);
  }
  else if (temperaturaoleo > topTEMPoleo || temperaturacab > topTEMPcab)
  {
    digitalWrite(ledR, LOW);
    digitalWrite(ledG, LOW);
    digitalWrite(ledY, HIGH);
  }
  else
  {
    digitalWrite(ledR, LOW);
    digitalWrite(ledG, HIGH);
    digitalWrite(ledY, LOW);
  }
  delay(250);
}