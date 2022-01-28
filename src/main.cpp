#include <max6675.h>

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

//temperature of the oil OIL
const byte dangerTEMPoleo = 80;
const byte maxTEMPoleo = 100;

//temp CYLINDER HEAD
const byte dangerTEMPcab = 160;
const byte maxTEMPcab = 200;

//time intervals
unsigned long previousMillis = 0;
const long interval = 350;

//RPMS
const byte maxRPM = 4000;
const byte medRPM = 2000;
const byte minRPM = 850;
float temperaturaoleo = 25;
float temperaturacab = 25;

void setup() {

  Serial.begin(9600);
  Serial.print("Oil,Cylinderhead,");
  Serial.println();
  pinMode(ledR, OUTPUT);
  pinMode(ledG, OUTPUT);
  pinMode(ledY, OUTPUT);
  pinMode(ledR, LOW);
  pinMode(ledG, LOW);
  pinMode(ledY, LOW);
  pinMode(12, OUTPUT); //PIN 12 IS USED AS A 5V SOURCE
  pinMode(13, LOW); //USING PIN 12 AS 5V SOURCE FOR MY TERMPOPAR
  //TO SHOW THAT ALL LEDS ARE WORKING
  digitalWrite(ledR, HIGH);
  delay(1000);
  digitalWrite(ledR, LOW);
  digitalWrite(ledG, HIGH);
  delay(1000);
  digitalWrite(ledG, LOW);
  digitalWrite(ledY, HIGH);
  delay(1000);
  digitalWrite(ledY, LOW);
  delay(1000);
  
}

void loop() {

  digitalWrite(12, HIGH); //USING PIN 12 AS 5V SOURCE FOR MY TERMPOPAR
  digitalWrite(13, LOW); //USING PIN 12 AS 5V SOURCE FOR MY TERMPOPAR

  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;
    float temperaturaoleo = thermocoupleoleo.readCelsius();
    float temperaturacab = thermocouplecab.readCelsius();
    Serial.print(temperaturaoleo);
    Serial.print(",");
    Serial.print(temperaturacab);
    Serial.print(",");
    Serial.println();
  }
  
  if (temperaturaoleo > maxTEMPoleo || temperaturacab > maxTEMPcab)
  {
    digitalWrite(ledR, HIGH);
    digitalWrite(ledG, LOW);
    digitalWrite(ledY, LOW);
  }
  else if (temperaturaoleo > dangerTEMPoleo || temperaturacab > dangerTEMPcab)
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
}