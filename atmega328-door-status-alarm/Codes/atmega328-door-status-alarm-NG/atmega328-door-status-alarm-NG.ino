/*
  Test code for ultrasonic-sensor-NG.h header file.
  -----------------------------------------------------------------------
  Test Points->
  - After every 2 seconds distance is measured and printed on serial port
  -----------------------------------------------------------------------
  Author
  Nandan Ghawate
  nandan.ghawate@gmail.com
  -----------------------------------------------------------------------
*/
/*pot readings-
clockwise 0
anticlockwise 415*/
#include "ultrasonic-sensor-NG.h"
#define greenLED 4
#define redLED 3
#define relayBJT 5
#define potTimer A1
unsigned long timer = 1000;
int relayStatus = 0;
unsigned long interval = 10000;
unsigned long previousMillis = 0;

int measuredDistance = 0;
void setupIo() {
  pinMode(greenLED, OUTPUT);
  pinMode(redLED, OUTPUT);
  pinMode(relayBJT, OUTPUT);
  digitalWrite(redLED, LOW);
  digitalWrite(greenLED, HIGH);
  digitalWrite(relayBJT, LOW);
}

void testGpio() {
  for (int i; i < 3; i++) {
    digitalWrite(greenLED, LOW);
    digitalWrite(redLED, HIGH);
    digitalWrite(relayBJT, HIGH);
    delay(300);
    digitalWrite(greenLED, LOW);
    digitalWrite(redLED, HIGH);
    digitalWrite(relayBJT, LOW);
    delay(300);
  }

}

unsigned long readPotTimer() {
  unsigned long sensorValue = analogRead(potTimer);
  Serial.print("sensorValue : ");
  Serial.println(sensorValue);
  unsigned long mappedSensorValue = map(sensorValue, 0, 416, 1000, 5000);
  Serial.print("Mapped Value : ");
  Serial.println(mappedSensorValue);
  delay(100);
  return mappedSensorValue;
}

void blinkRed(){
  digitalWrite(redLED, LOW);
  delay(100);
  digitalWrite(redLED, HIGH);
  delay(100);
}

void setup() {
  Serial.begin(115200);
  Serial.println("");
  Serial.println("Setting Up Door Status Alarm");
  setupUltrasonicSensor();
  setupIo();
  delay(1000);
  Serial.println("Checking Ultrasonic Sensor Now");
}

void loop() {
  unsigned long currentMillis = millis();
  previousMillis=currentMillis;
  while (measureDistanceUltrasonicSensor() > 6) {
    currentMillis = millis();
    if ((unsigned long)(currentMillis - previousMillis) >= interval) {
      digitalWrite(redLED, HIGH);
      digitalWrite(relayBJT, HIGH);
      Serial.println("Alarm Turned On");
      relayStatus = 1;
    }
    delay(100);
  }
  if (relayStatus == 1) {
    relayStatus = 0;
    digitalWrite(redLED, LOW);
    digitalWrite(relayBJT, LOW);
    Serial.println("Alarm Turned Off");
  }
}
