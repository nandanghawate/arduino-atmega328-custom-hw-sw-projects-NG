#include <ModbusMaster.h>
#include <SoftwareSerial.h> 

#define DE_RE 4
#define PID_RX 10
#define PID_TX 11
#define PID_BAUD 9600

ModbusMaster node;
SoftwareSerial PID_Serial(PID_RX,PID_TX);

void preTransmission() {
  digitalWrite(DE_RE, 1);
}

void postTransmission() {
  digitalWrite(DE_RE, 0);
}

void setup() {  
  pinMode(DE_RE, OUTPUT);
  digitalWrite(DE_RE, 0); // default receive

  Serial.begin(115200);
  PID_Serial.begin(PID_BAUD);
  delay(1000);
  Serial.print("Test CH's PID ");
  delay(1000);
}

void loop() {
  preTransmission();
  Serial.print("Sending Command 1");
  PID_Serial.print("05030164000285AC");
  postTransmission();
  int i = 0;
  while (i<20000) {
    if (PID_Serial.available()) {
      int inByte = PID_Serial.read();
      Serial.write(inByte);
    }
    i++;
  }
  delay(2000);
  Serial.print("Sending Command 2");
  PID_Serial.println("05030164000285AC");
  postTransmission();
  i = 0;
  while (i<20000) {
    if (PID_Serial.available()) {
      int inByte = PID_Serial.read();
      Serial.write(inByte);
    }
    i++;
  }
}