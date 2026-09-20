/*
Forest Ray
April 12, 2026
MPU 6050, Lab 12
*/

#include <Wire.h>

const int sensorAddr = 0x68; // sensor address 
float zAccelOffset = 0;
float zGyroOffset = 0;

int I2CScanner(bool isVerbose) {
  for (int addr = 1; addr < 127; addr++) {
    Wire.beginTransmission(addr); // Ping current address for the device
    if (!Wire.endTransmission()) {
      if (isVerbose){
        Serial.println("I2C Scanner: ");
        Serial.print("Device detected at: "); Serial.println(addr);
      }
      return addr;
    }
  }  return -1;
}

void wakeUp(int chipAddr) { // wake up the chip
  Wire.beginTransmission(chipAddr);
  Wire.write(0x6B); // Write to the power management register
  Wire.write(0x00); // Write 0x00 to register 0x6B 
  Wire.endTransmission();
}

byte whoAmI(bool isVerbose, int chipAddr) {
  Wire.beginTransmission(chipAddr); // start transmission
  Wire.write(0x75);                 // specify Who Am I register
  Wire.endTransmission();           // repeated start
  Wire.beginTransmission(chipAddr);
  Wire.requestFrom(chipAddr, 1);    // Request one Byte
  byte givenName = Wire.read();     // Read Byte
  Wire.endTransmission();

  if (isVerbose) { // print givenName 
    Serial.println("Who am I?");
    Serial.print("Binary: "); Serial.println(givenName, BIN);
    Serial.print("Hex: "); Serial.println(givenName, HEX);
  } 
  return givenName; // Return address 
}

int getAccelerationZ(int chipAddr) {
  Wire.beginTransmission(chipAddr); // start transmission
  Wire.write(0x3F);                 // Z-accelerometer register
  Wire.endTransmission();           // Repeated Start
  Wire.beginTransmission(chipAddr);
  Wire.requestFrom(chipAddr, 2);   // request the to az bytes
  int highByte = Wire.read();
  int lowByte  = Wire.read();
  Wire.endTransmission();

  // combine high and low byte 
  int zAcceleration = ((highByte << 8) | (lowByte)); 
  return zAcceleration;
}

float getOffsetAccelZ(int chipAddr, int iters) {
  float expectedValue = 16384.0; // value the sensor should read for g 

  // get the average value from sensor
  float measuredSum = 0;
  for (int ii = 0; ii < iters; ii++) {
    measuredSum += getAccelerationZ(chipAddr);
  }
  float measuredAverage = measuredSum/iters;

  // compute and return offset
  return (expectedValue - measuredAverage);
}

int getGyroZ(int chipAddr) {
  Wire.beginTransmission(chipAddr); // start transmission
  Wire.write(0x47);                 // Z-gyroscop register
  Wire.endTransmission();           // Repeated Start
  Wire.beginTransmission(chipAddr);
  Wire.requestFrom(chipAddr, 2);    // request the to z-gyro bytes
  int highByte = Wire.read();
  int lowByte  = Wire.read();
  Wire.endTransmission();

  // combine high and low byte 
  int zGyro = ((highByte << 8) | (lowByte)); 
  return zGyro;
}

float getOffsetGyroZ(int chipAddr, int iters) { 
  float expectedValue = 0;

  // get the average value from sensor
  float measuredSum = 0;
  for (int ii = 0; ii < iters; ii++) {
    measuredSum += getGyroZ(chipAddr);
  }
  float measuredAverage = measuredSum/iters;

  // compute offset and return
  return (expectedValue - measuredAverage);
}

void setup() {
  Serial.begin(9600); Serial.println("Starting up...");
  Wire.begin();

  // make sure the chip is awake
  Serial.println("Waking Up Chip...");
  wakeUp(sensorAddr);

  // verify address with i2c scan and whoAmI register
  Serial.println("Verifying Chip Address...");
  Serial.println(I2CScanner(true), HEX);
  Serial.println(whoAmI(true, sensorAddr), HEX);
  
  // compute offset for z acceleration
  zAccelOffset = getOffsetAccelZ(sensorAddr, 100);
  // compute offset for z gyro
  zGyroOffset = getOffsetGyroZ(sensorAddr, 100);

  delay(100);
}

void loop() {
  // get acceleration
  int rawAccelZ = getAccelerationZ(sensorAddr); // get measurement from IMU
  float accelZ = (9.81/16384.0)*(rawAccelZ + zAccelOffset);
  Serial.print("Accel: "); Serial.println(accelZ);

  // get gyro
  int rawGyroZ = getGyroZ(sensorAddr);
  float gyroZ = (rawGyroZ + zGyroOffset)/131.0;
  Serial.print("Gyro: "); Serial.println(gyroZ);
  
  delay(500);
}
