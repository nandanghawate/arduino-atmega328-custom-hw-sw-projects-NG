/*
 Header File for Ultrasonic Interfacing to Arduino Nano
-----------------------------------------------------------------------
Connections->
 Ultrasonic Sensor  | Arduino Nano
 Trigger Pin -------> D8
 Echo Pin ----------> D9
-----------------------------------------------------------------------
Formula->
D = 1/2 × T × C
D is the distance,
T is the time between the Triggering and Echo,
C is the speed of sound.
-----------------------------------------------------------------------
Author
Nandan Ghawate
nandan.ghawate@gmail.com
-----------------------------------------------------------------------
*/

/* Declarations*/
#define triggerPin 8
#define echoPin 9
long timePassed = 0;
int distance = 0;

/* setupUltrasonicSensor()- setup function for ultrasonic pins */
void setupUltrasonicSensor() {
  pinMode(triggerPin, OUTPUT); //Set triggerPin as an Output
  pinMode(echoPin, INPUT); //Set echoPin as an Input
}


/* measureDistanceUltrasonicSensor()-
   Measures and Returns distance as int type.
*/
int measureDistanceUltrasonicSensor(){
  digitalWrite(triggerPin, LOW);
  delayMicroseconds(2);
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin, LOW);  //give Trigger pulse

  timePassed = pulseIn(echoPin, HIGH); //wait For echo
  distance = timePassed*0.034/2;
  return distance;
}

/*--------------------------------------------------------------------------*/
