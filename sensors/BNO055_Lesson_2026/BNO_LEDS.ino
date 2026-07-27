/*
BNO LEDs
Author: Forest Ray
Date: May 29, 2026

Control LEDs via tilt with BNO055
*/

#include <Wire.h>
#define BNOAddress 0x28
#define OPR_MODE   0x3D
#define UNIT_SEL   0x3B

// LED Pins
const int NORTH_PIN = 5;
const int SOUTH_PIN = 2;
const int EAST_PIN  = 3;
const int WEST_PIN  = 4;

void setup() {
  // Setup pins
  pinMode(NORTH_PIN, OUTPUT);
  pinMode(SOUTH_PIN, OUTPUT);
  pinMode(EAST_PIN,  OUTPUT);
  pinMode(WEST_PIN,  OUTPUT);

  Serial.begin(115200);
  delay(1000);

  Serial.println("Beginning Communication...");
  Wire.begin();
  
  // BNO Settings
  // IMU mode
  Wire.beginTransmission(BNOAddress);
  Wire.write(OPR_MODE);
  Wire.write(1<<3);
  Wire.endTransmission();
  // Degrees
  Wire.beginTransmission(BNOAddress);
  Wire.write(UNIT_SEL);
  Wire.write(0<<2);
  Wire.endTransmission();
  delay(1000);
}

void loop() {
  Wire.beginTransmission(BNOAddress); // start transmitting to sensor
  
  // get heading from 0x1A - 0x1F
  Wire.write(0x1A);
  Wire.endTransmission(); // Repeated Start
  Wire.requestFrom(BNOAddress, 6);

  // angle x
  uint8_t LSB = Wire.read();
  uint8_t MSB = Wire.read();

  int Eul_x = (((int)MSB<<8 | LSB) >> 4);

  LSB = Wire.read();
  MSB = Wire.read();

  int Eul_y = (((int)MSB<<8 | LSB) >> 4);

  LSB = Wire.read();
  MSB = Wire.read();
  
  int Eul_z = (((int)MSB<<8 | LSB) >> 4);

  Serial.print(Eul_x); Serial.print(", ");
  Serial.print(Eul_y); Serial.print(", ");
  Serial.println(Eul_z);

  // Control North and South LEDs

  if (Eul_z >= 30) { 
    digitalWrite(NORTH_PIN, HIGH);
    digitalWrite(SOUTH_PIN, LOW);
  } else if (Eul_z <= -30) {
    digitalWrite(SOUTH_PIN, HIGH);
    digitalWrite(NORTH_PIN, LOW);
  } else if ((Eul_z > -30) && (Eul_z < 30)) {
    digitalWrite(NORTH_PIN, LOW);
    digitalWrite(SOUTH_PIN, LOW);
  }

  // control east and west LEDs
  if (Eul_y >= 30) {
    digitalWrite(EAST_PIN, HIGH);
    digitalWrite(SOUTH_PIN, LOW);
  } else if (Eul_y <= -30) { 
    digitalWrite(WEST_PIN, HIGH);
    digitalWrite(EAST_PIN, LOW);
  } else if ((Eul_y > -30) && (Eul_y < 30)) {
    digitalWrite(EAST_PIN, LOW);
    digitalWrite(WEST_PIN, LOW);
  }

  delay(100);
}
