/*
ASCII TABLE
Author: Forest Ray
Date: June 7, 2026
Credit: Adapted from work by Nicholas Zambetti and Tom Igoe
https://docs.arduino.cc/built-in-examples/communication/ASCIITable/

Print your own ASCII table. 
*/

void setup() {
  // Initialize Serial
  Serial.begin(9600); // baud: 9600 symbols/second

  // Wait for Serial port to connect
  while (!Serial) {}

  // Print the title of the ASCII table
  Serial.println("ASCII Table");

  // 33 through 126 are the visible ASCII characters
  for (int ii = 33; ii <= 126; ii++) {
    // The Serial monitor interprets all Bytes as ASCII
    Serial.write(ii);        // Show the symbol
    Serial.print(", dec: "); // Print as ASCII-encoded decimal
    Serial.print(ii);        // or Serial.print(thisByte, DEC)
    Serial.print(", hex: "); // Print as HEX 
    Serial.println(ii, HEX);
  }

}

void loop() {}
