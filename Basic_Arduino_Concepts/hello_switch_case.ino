/*
Switch Case: Hello World
Author: Forest Ray
Date: May 25, 2026
*/

// Global Variables
const byte BUTTON_PIN = 8;   // input pin for active high button
int languageMode      = 0;   // specify language 
bool previousState    = LOW; // keep track of button state
bool currentState     = LOW; // current loop button state

// Functions
String change_language(int languageModeP) {
/* 
change_language
- Is given language mode that is changed via button press and returns
  "hello world" in a language specified by the number of button presses
Arguments:
- (int) languageModeP - specify which language to return message in 
Return:
- (String) return_message - "Hello, world!" in language specified by
  language mode  
*/

  String return_message = "Error: Invalid Language Mode";
  
  switch (languageModeP) {
    case 0: // English
      return_message = "Hello World!";
      break;
    case 1: // Hungarian
      return_message = "Helló világ!";
      break;
    case 2: // Latvian
      return_message = "Sveika, Pasaule!";
      break;
    default: 
      return_message = "Error: Invalid Language Mode";
      break;  
  } // end switch

  return return_message; 
}

bool check_button_state(byte buttonPinP, bool previousStateP) {
/*
check_button_state
- Look at the state of the specified pin and compare it to the previous state.
  Return true if a valid button press has occured. This function is specifically
  for an active high button. 
Arguments:
- (byte) buttonPinP - the input pin connected to the button
- (bool) previousStateP - the state to compare the current state of the button to
Return:
- (bool) buttonPress - return true if the button is being pressed
*/

  bool buttonState = digitalRead(buttonPinP); // check state of button
  bool buttonPress = false;

  if ((buttonState!=previousStateP) && buttonState) {
    buttonPress = true;
  }

  return buttonPress;  
}

// Main Code 
void setup() {
  Serial.begin(9600);         // baud rate is 9600
  pinMode(BUTTON_PIN, INPUT); // set input for button 
}

void loop() {
  // check button state 
  currentState = check_button_state(BUTTON_PIN, previousState);

  if (currentState) {
    if (languageMode == 2) {
      languageMode = 0; // if max mode number, reset to 0 
      Serial.println(change_language(languageMode));
    } else {
      languageMode++; // increment mode 
      Serial.println(change_language(languageMode));
    } // end if else
    previousState = currentState; // update state 
  } else { previousState = currentState; }
  // end if else

  // I usually use a shorter debounce 
  // but this code is particularly bounce prone 
  delay(50); // debounce 
}
