
const float sensorPin = A0;
const int redLedPin = 5;
const int greenLedPin = 6;
const int yellowLedPin = 7;

void setup()
{
  pinMode(redLedPin, OUTPUT);
  pinMode(greenLedPin, OUTPUT);
  pinMode(yellowLedPin, OUTPUT);
  Serial.begin(9600);
  Serial.print("Sensor aquecendo\n");
  delay(10000);
}

void loop()
{
  float sensorValue = analogRead(sensorPin);
  Serial.print("Valor do sensor: ");
  Serial.println(sensorValue);

  if (sensorValue >= 600)
  {
    digitalWrite(greenLedPin, LOW);
    digitalWrite(redLedPin, HIGH);
    digitalWrite(yellowLedPin, LOW);
  }
  else if (sensorValue >= 400)
  {
    digitalWrite(greenLedPin, LOW);
    digitalWrite(redLedPin, LOW);
    digitalWrite(yellowLedPin, HIGH);
  }
  else if (sensorValue > 300 && sensorValue <= 350)
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

  delay(1000);
}
