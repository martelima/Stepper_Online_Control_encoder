#include <Wire.h>
#include <LiquidCrystal.h>
#include <LiquidCrystal_I2C.h>
#include <Ultrasonic.h>

Ultrasonic ultrassom(7, 6);
LiquidCrystal_I2C lcd(0x3F, 16, 2);
int distancia = 0;
/* ======================================================================================================
   
   Usina Info & WR Kits
   
   Medindo RPM de um Motor DC com Arduino
   
   www.wrkits.com.br | facebook.com/wrkits | youtube.com/canalwrkits


   HARDWARE:
 

   ARDUINO    ENCODER

   GND          GND
   5V            5V
   D2           OUT

====================================================================================================== */

 
// ========================================================================================================
// --- Variáveis Globais --- 
int           rpm;
volatile byte pulsos;
unsigned long timeold;

//Altere o numero abaixo de acordo com o seu disco encoder
unsigned int pulsos_por_volta = 50;


// ========================================================================================================
// --- Interrupção ---
void contador()
{
  //Incrementa contador
  pulsos++;
}


// ========================================================================================================
// --- Configurações Iniciais ---
void setup()
{
  Serial.begin(9600);
  lcd.begin();
  pinMode(2, INPUT);
   
  
  //Interrupcao 0 - pino digital 2
  //Aciona o contador a cada pulso
  attachInterrupt(0, contador, RISING);
  pulsos  = 0;
  rpm     = 0;
  timeold = 0;
  
} //end setup


// ========================================================================================================
// --- Loop Infinito ---
void loop()
{
  //Atualiza contador a cada segundo
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
  
} //end loop
