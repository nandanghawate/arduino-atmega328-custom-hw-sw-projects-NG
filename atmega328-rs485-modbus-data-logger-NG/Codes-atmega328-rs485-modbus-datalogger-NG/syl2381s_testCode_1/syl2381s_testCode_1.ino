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
 
  node.begin(1, PID_Serial);
  node.preTransmission(preTransmission);
  node.postTransmission(postTransmission);
  delay(1000);
  Serial.print("Test CH/'s PID ");
  delay(1000);
}

void loop() {
  uint8_t readData;
  readData = node.readHoldingRegisters(0x0000H,1);
  Serial.print("Read Data at 0x0000H is: ");
  Serial.println(readData);
  Serial.println(node.getResponseBuffer(0));
  delay(2000);
  readData = node.readHoldingRegisters(0x0001H,1);
  Serial.print("Read Data at 0x0001H is: ");
  Serial.println(readData);
  Serial.println(node.getResponseBuffer(0));
  delay(2000);
  readData = node.readHoldingRegisters(0x0002H,1);
  Serial.print("Read Data at 0x0002H is: ");
  Serial.println(readData);
  Serial.println(node.getResponseBuffer(0));
  delay(2000);
  readData = node.readHoldingRegisters(0x0003H,1);
  Serial.print("Read Data at 0x0003H is: ");
  Serial.println(readData);
  Serial.println(node.getResponseBuffer(0));
  delay(2000);
  readData = node.readHoldingRegisters(0x0004H,1);
  Serial.print("Read Data at 0x0004H is: ");
  Serial.println(readData);
  Serial.println(node.getResponseBuffer(0));
  delay(2000);
  readData = node.readHoldingRegisters(0x0005H,1);
  Serial.print("Read Data at 0x0005H is: ");
  Serial.println(readData);
  Serial.println(node.getResponseBuffer(0));
  delay(2000);
}
