#include <ArduinoJson.h>
#include <SD.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

const float sensorPin = A0;
const int chipSelect = 10;
LiquidCrystal_I2C lcd(0x27,16,2);
File dados;
int pushButton = 2;
bool estadoBotao = false;



void setup()
{
  lcd.init();
  lcd.backlight();
  Serial.begin(9600);
  Serial.print("Sensor aquecendo\n");
  lcd.setCursor(0, 0); //coluna 0 linha 0
  lcd.print("Aquecendo...");
  delay(5000);
  lcd.clear();

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

void medicao()
{
  lcd.clear();
  lcd.setCursor(0, 0); //coluna 0 linha 0
  lcd.print("Aproxime o ");
  lcd.setCursor(0, 1); //coluna 0 linha 0
  lcd.print("sensor");
  delay(3000);
  lcd.clear();
  float sensorValue = analogRead(sensorPin);
  Serial.print("Valor do sensor: ");
  Serial.println(sensorValue);
  lcd.setCursor(0, 0); //coluna 0 linha 0
  lcd.print("Medindo...");
  delay(5000);
  lcd.clear();

  if (sensorValue >= 600)
  {
	lcd.setCursor(0, 0); //coluna 0 linha 0
  lcd.print("Percentual de ");
  lcd.setCursor(0, 1); //coluna 0 linha 0
  lcd.print("alcool: elevado");
  delay(5000);
  lcd.clear();
  
  }
  else if (sensorValue >= 400)
  {
  lcd.setCursor(0, 0); //coluna 0 linha 0
	lcd.print("Percentual de ");
  lcd.setCursor(0, 1); //coluna 0 linha 0
  lcd.print("alcool: medio");
  delay(5000);
  lcd.clear();
  }
  else if (sensorValue > 300 && sensorValue <= 350)
  {
  lcd.setCursor(0, 0); //coluna 0 linha 0
  lcd.print("Percentual de ");
  lcd.setCursor(0, 1); //coluna 0 linha 0
  lcd.print("alcool: baixo");
  delay(5000);
  lcd.clear();
  }
  else
  {
	lcd.setCursor(0, 0); //coluna 0 linha 0
  lcd.print("Nada de alcool!!");
  delay(5000);
  lcd.clear();
  }

  salvarDados(sensorValue);
  
  lcd.setCursor(0, 0); //coluna 0 linha 0
  lcd.print("Salvando...");
  delay(10000);
  lcd.clear();
  //lerDados();
}

void loop()
{
  if (digitalRead(pushButton) == LOW && !estadoBotao) // Verifica se o botão foi pressionado (LOW) e não está pressionado antes
  {
    estadoBotao = true; // Define a flag para evitar chamadas repetidas
    medicao();
  }

  if (digitalRead(pushButton) == HIGH)
  {
    estadoBotao = false; // Quando o botão é solto, redefina a flag
    lcd.setCursor(0, 0); //coluna 0 linha 0
    lcd.print("Pronto para uso");
    
  }
}
