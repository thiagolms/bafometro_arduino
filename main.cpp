const int sensorPin = A0;       // Pino analógico para o sensor de álcool
const int redLedPin = 6;        // Pino do LED vermelho
const int greenLedPin = 7;      // Pino do LED verde
const int yellowLedPin = 5;     // Pino do LED amarelo
const float alcoholThreshold = 0.05; // Limite de álcool em mg/L

void setup() {
  pinMode(redLedPin, OUTPUT);     // Configura o pino do LED vermelho como saída
  pinMode(greenLedPin, OUTPUT);   // Configura o pino do LED verde como saída
  pinMode(yellowLedPin, OUTPUT);  // Configura o pino do LED amarelo como saída
}

void loop() {
  /* int sensorValue = 450;*/     // Defina um valor para testar os Leds e condicionais
  int sensorValue = analogRead(sensorPin);  // Lê o valor do sensor

  float voltage = sensorValue * (5.0 / 1023.0);  // Converte o valor para tensão (0-5V)
  float alcoholLevel = map(voltage, 0.0, 5.0, 0, 500);  // Mapeia a tensão para uma escala de nível de álcool (0-500)

  if (alcoholLevel >= 200) {
    digitalWrite(greenLedPin, LOW);    // Desliga o LED verde
    digitalWrite(redLedPin, HIGH);     // Liga o LED vermelho
    digitalWrite(yellowLedPin, LOW);   // Desliga o LED amarelo
  } else if (alcoholLevel >= 100) {
    digitalWrite(greenLedPin, LOW);    // Desliga o LED verde
    digitalWrite(redLedPin, LOW);      // Desliga o LED vermelho
    digitalWrite(yellowLedPin, HIGH);  // Liga o LED amarelo
  } else if (alcoholLevel < alcoholThreshold * 1000) {
    digitalWrite(greenLedPin, HIGH);   // Liga o LED verde
    digitalWrite(redLedPin, LOW);      // Desliga o LED vermelho
    digitalWrite(yellowLedPin, LOW);   // Desliga o LED amarelo
  } else {
    digitalWrite(greenLedPin, LOW);    // Desliga o LED verde
    digitalWrite(redLedPin, LOW);      // Desliga o LED vermelho
    digitalWrite(yellowLedPin, LOW);   // Desliga o LED amarelo
  }

  delay(1000);  // Aguarda 1 segundo antes de fazer a próxima leitura
}
