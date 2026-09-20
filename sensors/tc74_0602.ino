/*
TC74 
Author: Forest Ray
Date:   June 2, 2026
*/

#include <Wire.h> // Library needed for I2C comms
#define sensorAddress 0x4D // TC74 Address  
#define tempRegister 0x00  // temperature register

int i2c_scanner() {
 /*
 i2c_scanner
 - looks for a single device and return the address
 Arguments: None
 Return:
 - (int) address - the address of the i2c device 
 */
 
  // for possible peripheral device addresses 
  for (int address=1; address<=127; address++) {
    Wire.beginTransmission(address); // begin transmission to address
    if (!Wire.endTransmission()) { // check for acknowledgement 
      return address; // if acknowledged, return address
    }
  }

  Serial.println("No Device Found"); // if no address is returned 
}

int read_temperature() {
/*
read_temperature
Arguments: None
Returns
- (int) rawReading - reading from the temperature sensor in Celsius 
*/
  // Get data from the sensor
  Wire.beginTransmission(sensorAddress); // transmit to sensor
  Wire.write(tempRegister);              // ask for temperature register
  Wire.endTransmission();                // reverse data direction, repeated start
  Wire.requestFrom(sensorAddress, 1);    // request 1 byte
  int rawReading = Wire.read();          // read byte

  return rawReading;
}
void setup() {
  Serial.begin(115200); // Fast Baud Rate 
  Wire.begin();         //  Join as a central device, no argument

  delay(1000); // I like to just give everything a second when starting up

  // scan for a peripheral device
  Serial.println("Searching for device....");
  Serial.print("0x"); Serial.println(i2c_scanner(), HEX); // print address
}

void loop() {
  Serial.print(read_temperature()); Serial.println("°C");
  delay(500);
}
