#define sirene 3
int frequencia = 0;
int tempo = 10;
// Programa : Ponte H L298N e motor de passo
// Autor : Mateus Lima

// Conexoes modulo - Arduino
int IN1 = 8;
int IN2 = 9;
int IN3 = 10;
int IN4 = 11;
int leitura = 0;

void setup()
{
  // Define os pinos como saida
  Serial.begin(9600);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
}

void loop()
{
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
