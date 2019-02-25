#include <Wire.h>
#include <LiquidCrystal.h>
#include <LiquidCrystal_I2C.h>
#include <Ultrasonic.h>
#define sirene 3
int frequencia = 0;
int tempo = 10;
// Programa : Ponte H L298N e motor de passo
// Autor : Arduino e Cia

// Conexoes modulo - Arduino
int IN1 = 8;
int IN2 = 9;
int IN3 = 10;
int IN4 = 11;
int leitura = 0;
Ultrasonic ultrassom(7, 6);
LiquidCrystal_I2C lcd(0x3F, 16, 2);
int distancia = 0;
int           rpm;
volatile byte pulsos;
unsigned long timeold;

//Altere o numero abaixo de acordo com o seu disco encoder
unsigned int pulsos_por_volta = 50;

void contador()
{
  //Incrementa contador
  pulsos++;
}

void setup()
{
  // Define os pinos como saida
  Serial.begin(9600);
  lcd.begin();
  pinMode(2, INPUT);
  attachInterrupt(0, contador, RISING);
  pulsos  = 0;
  rpm     = 0;
  timeold = 0;
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
}

void loop()
{
    if (millis() - timeold >= 1000)
  {
    //Desabilita interrupcao durante o calculo
    detachInterrupt(0);
    rpm = (60 * 1000 / pulsos_por_volta ) / (millis() - timeold) * pulsos;
    timeold = millis();
    pulsos = 0;

    //Mostra o valor de RPM no serial monitor
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("RPM =");
    Serial.print("RPM = ");
    lcd.setCursor(6,0);
    lcd.print(rpm,DEC);
    Serial.println(rpm, DEC);
    //Habilita interrupcao
    attachInterrupt(0, contador, RISING);
  }
  int leitura = analogRead(A0);
  if (leitura > 300) {
    // Passo 1
    digitalWrite(IN1, 1);
    digitalWrite(IN2, 0);
    digitalWrite(IN3, 0);
    digitalWrite(IN4, 1);
    delay(tempo);

    // Passo 2
    digitalWrite(IN1, 0);
    digitalWrite(IN2, 1);
    digitalWrite(IN3, 0);
    digitalWrite(IN4, 1);
    delay(tempo);

    // Passo 3
    digitalWrite(IN1, 0);
    digitalWrite(IN2, 1);
    digitalWrite(IN3, 1);
    digitalWrite(IN4, 0);
    delay(tempo);

    // Passo 4
    digitalWrite(IN1, 1);
    digitalWrite(IN2, 0);
    digitalWrite(IN3, 1);
    digitalWrite(IN4, 0);
    delay(tempo);
  } else {
    for (frequencia = 150; frequencia < 1800; frequencia += 1) {
      tone(sirene, frequencia, tempo);
      delay(1);
    }
    for (frequencia = 1800; frequencia > 150; frequencia -= 1) {
      tone(sirene, frequencia, tempo);
      delay(1);
      digitalWrite(IN1, 0);
      digitalWrite(IN2, 0);
      digitalWrite(IN3, 0);
      digitalWrite(IN4, 0);
    }
  }
}
