/*
Basic Sonic Ranger 
Forest Ray
September 20, 2026

Convert sonic ranger signal to a distance using the speed of sound. 
*/

// Globals
const int TRIGPIN = 13; // Pin used to trigger sonic ranger
const int ECHOPIN = 12; // pin that times signal

long getDuration() {
  digitalWrite(TRIGPIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIGPIN, HIGH);
  delayMicroseconds(10); // trig pin needs to be high for 10 micro seconds
  digitalWrite(TRIGPIN, LOW);

  return pulseIn(ECHOPIN, HIGH); // measure the time from echo pin
}

void setup() {
  Serial.begin(9600); // baud rate

  pinMode(TRIGPIN, OUTPUT); // output because we are writing to it
  pinMode(ECHOPIN, INPUT); // input because we are reading from it

  digitalWrite(TRIGPIN, LOW); // make sure the trigger starts low
}

void loop() {
  float duration = getDuration(); // measure duration for signal 
  float distance = (duration/2.0) * 0.0343; // get distance in centimeters
  Serial.println(distance);
  delay(10);
}
