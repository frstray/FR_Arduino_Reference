/* 
User Input
June 8, 2026
Forest Ray

This program originates from the following Arduino forum post.
https://forum.arduino.cc/t/serial-input-basics-updated/382007/2. 

This is a wonderful basic formula for dealing with user input at the Serial monitor.
I use this framework constantly, but it did not originate with me. Everyone say
"Thank you user Robin2 from the Arduino Forum!!"
*/


// Variables for Serial read
const byte numChars = 32;     // This is the size of your character array
char receivedChars[numChars]; // make the array
boolean newData = false;      // by default there is no new data to process


void receiveData(){
  static byte ndx = 0;    // The index of the character being recieved
  char startMarker = '<'; // this character marks the beginning of the message
  char endMarker = '>';   // This character marks the end of the message
  char rc;                // rc stands for "recieved character" 
  static boolean recvInProgress = false; // Is there a message currently being read?

  while (Serial.available() > 0 && newData == false) { // while there is a message sent and the data isn't new 
    rc = Serial.read();

    if (recvInProgress == true) { // If we're currently reading a message
      if (rc != endMarker) {      // If the end marker has NOT been reached
        receivedChars[ndx] = rc;  // The character at the updated index is rc
        ndx++;                    // update index
        if (ndx >= numChars) {
          ndx = numChars - 1;
        }
      }
      else {                       // End marker has been reached
        receivedChars[ndx] = '\0'; // terminate the string
        recvInProgress = false;    // We have finished receiving
        ndx = 0;                   // Reset index
        newData = true;            // There is data available 
      }
    }
    else if (rc == startMarker) {
      recvInProgress = true; // if we reach a start marker, start recieving message
    }
    
  }
}

// This function handle the serial commands
void showNewData(){
  if (newData == true){
    Serial.print("This just in...");
    Serial.println(receivedChars);
    newData = false;
  }
}

void setup() {
  Serial.begin(9600); // Start serial with 9600 baud rate
  Serial.println("<Arduino is ready>");
}

void loop() {
  receiveData();
  showNewData();
}


