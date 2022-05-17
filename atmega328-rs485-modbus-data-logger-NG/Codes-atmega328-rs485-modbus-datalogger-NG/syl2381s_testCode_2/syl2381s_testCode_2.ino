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
  PID_Serial.begin(9600);
 
  node.begin(1, PID_Serial);
  node.preTransmission(preTransmission);
  node.postTransmission(postTransmission);
  delay(1000);
  Serial.println("Test CH's PID ");
  delay(1000);
}
void loop() {
  uint16_t readData;
  uint16_t readDataReturn;
  
  Serial.println("2 register read :");
  readData = node.readHoldingRegisters(0x0164, 2);
  readDataReturn = node.writeMultipleRegisters (0x0000, 100);
  if (readData == node.ku8MBSuccess) {
    Serial.print("\nPV: ");
    Serial.println(node.getResponseBuffer(0));
  }
  else {
    Serial.print("\nError: ");
    Serial.println(readData, HEX);
    Serial.print("\nError: ");
    Serial.println(readDataReturn, HEX);
  }
  delay(5000);

  Serial.println("1 register read :");
  readData = node.readHoldingRegisters(0x0164, 1);

  if (readData == node.ku8MBSuccess) {
    Serial.print("\nPV: ");
    Serial.println(node.getResponseBuffer(0));
  }
  else {
    Serial.print("\nError: ");
    Serial.println(readData, HEX);
  }
  delay(5000);
}

