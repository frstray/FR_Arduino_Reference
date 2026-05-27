/*
You Have 10 seconds Left
Author: Forest Ray
Date: May 26, 2026

An illustration of if and else if using a count down timer. 
*/

// Globals
long startTime = 0;
// keep track of whether the timer has been triggered
bool endTimerTriggered     = false;
bool halfTimerTriggered    = false;
bool quarterTimerTriggered = false;

void setup() {
  Serial.begin(9600); // baud rate is 9600

  // let user know the clock is about to start
  Serial.println("Starting the clock...");
  delay(5000); // give time to open serial monitor 
  Serial.println("You have 10 seconds!");

  startTime = millis(); // start the clock
}

void loop() {
  
  if (((millis()-startTime) >= 10000) && (!endTimerTriggered)) {
    Serial.println("Your time is up!");
    endTimerTriggered = true;
  } else if (((millis()-startTime) >= 5000) && (!halfTimerTriggered)) {
    Serial.println("You have used half of your time!");
    halfTimerTriggered = true;
  } else if (((millis()-startTime) >= 2500) && (!quarterTimerTriggered)) {
    Serial.println("You have used a quarter of your time!");
    quarterTimerTriggered = true; 
  }

}
