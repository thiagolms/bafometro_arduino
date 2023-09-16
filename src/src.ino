#include <ArduinoJson.h>
#include <SD.h>


const float sensorPin = A0;
const int redLedPin = 5;
const int greenLedPin = 6;
const int yellowLedPin = 7;
const int chipSelect = 10;

File dados;

void setup()
{
  pinMode(redLedPin, OUTPUT);
  pinMode(greenLedPin, OUTPUT);
  pinMode(yellowLedPin, OUTPUT);
  Serial.begin(9600);
  Serial.print("Sensor aquecendo\n");
  delay(10000);

  if (!SD.begin(chipSelect))
  {
    Serial.println("Falha na inicialização do cartão");
    return;
  }
}

void salvarDados(float sensorValue)
{
  dados = SD.open("dados.txt", FILE_WRITE);
  if (dados)
  {
    DynamicJsonDocument jsonDoc(128);
    jsonDoc["valor"] = sensorValue;
    serializeJson(jsonDoc, dados);
    dados.println();
    dados.close();
  }
}

void lerDados()
{
  dados = SD.open("dados.txt");
  if (dados)
  {
    Serial.println("Conteúdo de dados.txt:");
    while (dados.available())
    {
      Serial.write(dados.read());
    }
    dados.close();
  }
  else
  {
    Serial.println("Erro ao abrir dados.txt para leitura.");
  }
}

void loop()
{
  float sensorValue = analogRead(sensorPin);
  // Serial.print("Valor do sensor: ");
  // Serial.println(sensorValue);

  if (sensorValue >= 400)
  {
    digitalWrite(greenLedPin, LOW);
    digitalWrite(redLedPin, HIGH);
    digitalWrite(yellowLedPin, LOW);
  }
  else if (sensorValue >= 200)
  {
    digitalWrite(greenLedPin, LOW);
    digitalWrite(redLedPin, LOW);
    digitalWrite(yellowLedPin, HIGH);
  }
  else if (sensorValue > 150 && sensorValue <= 195)
  {
    digitalWrite(greenLedPin, HIGH);
    digitalWrite(redLedPin, LOW);
    digitalWrite(yellowLedPin, LOW);
  }
  else
  {
    digitalWrite(greenLedPin, LOW);
    digitalWrite(redLedPin, LOW);
    digitalWrite(yellowLedPin, LOW);
  }

  salvarDados(sensorValue);

  delay(10000);

  lerDados();
}
