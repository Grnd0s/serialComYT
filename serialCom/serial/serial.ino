#include <ArduinoJson.h>

int ledBlue = 2;

String receivedString;
bool ledState = true;

// the setup routine runs once when you press reset:
void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
  pinMode(ledBlue, OUTPUT);
}

void printStatus()
{
  DynamicJsonDocument order(2048);
  order["STATUS"] = ledState ? "ON" : "OFF";
  serializeJson(order, Serial);
  Serial.println();
}

// the loop routine runs over and over again forever:
void loop() {

  if (Serial.available() > 0)
  {
    receivedString = Serial.readString();
    Serial.print("RECV: ");
    Serial.println(receivedString);
    DynamicJsonDocument order(2048);
    deserializeJson(order, receivedString);
    if (order.containsKey("LED") && order["LED"])
    {
      digitalWrite(ledBlue, HIGH);
      ledState = true;
    }
    else if (order.containsKey("LED") && !order["LED"])
    {
      digitalWrite(ledBlue, LOW);
      ledState = false;
    }
    if (order.containsKey("STATUS") && order["STATUS"])
    {
      printStatus();
    }
  }
  
}
