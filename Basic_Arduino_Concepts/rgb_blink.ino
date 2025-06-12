/*
 * Forest Ray
 * June 12, 2025
 * 
 * Use an RGB LED
 * tested on Giga and Uno
 */
 
// GLOBALS
  byte RED_PIN   = 11;
  byte GREEN_PIN = 10;
  byte BLUE_PIN  = 9;

// FUNCTIONS
/*
 * SetRGB
 * Arguments:
 * - red   (int): value from 0-255 indicating how much red in color
 * - green (int): value from 0-255 indicating how much green in color
 * - blue  (int): value from 0-255 indicating how much blue in color
 */
void SetRGB(int red, int green, int blue){
  analogWrite(RED_PIN,   red);
  analogWrite(GREEN_PIN, green);
  analogWrite(BLUE_PIN,  blue);
}

// SETUP
void setup() {
  // Setup LED PINS
  pinMode(RED_PIN,   OUTPUT);
  pinMode(GREEN_PIN, OUTPUT);
  pinMode(BLUE_PIN,  OUTPUT);
}

// LOOP
void loop() {
  // blue
  SetRGB(0, 0, 255);
  delay(1000);

  // green
  SetRGB(0, 255, 0);
  delay(1000);

  // red
  SetRGB(255, 0, 0);
  delay(1000);
}
