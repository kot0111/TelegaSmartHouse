/* Код для прошивки Arduino Uno
Автор - kot0111
*/
#include <SoftwareSerial.h>
#include <SPI.h>
#include <math.h>
#define TEMP_PIN A3
#define REL_PIN 12
SoftwareSerial esp(4, 5);
void setup() {
  esp.begin(9600);
  pinMode(REL_PIN, OUTPUT);
}
void loop() {
  String command = esp.readStringUntil('\n');
  command.trim();
  if (command == "turnOn") {
    digitalWrite(REL_PIN, HIGH);
  }
  if (command == "turnOff") {
    digitalWrite(REL_PIN, LOW);
  }
  if (command == "tempUpd") {
    float voltage = analogRead(TEMP_PIN) / 1024.0 * 5.0 - 0.5;
    float temp = voltage * 100.0;
    esp.println  (temp);
  }
}
