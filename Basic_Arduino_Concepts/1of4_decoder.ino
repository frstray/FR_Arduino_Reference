/*
Forest Ray
February 2, 2026
2-line to 1-of-4 decoder 
(E2 Take Home Quiz Problem 1)

The goal of this program is to perform the function of a 
2-line to 1-of-4 decoder. It takes two inputs (A, B),
and returns one of four outputs (0, 1, 2, 3). 

We want to turn on one of four LEDs based on the 
output. Each output will be an index to an array 
holding each LED pin. 

  A  |  B  |  Binary Num  |  Output  |
  0  |  0  |  00          |  0       |
  0  |  1  |  01          |  1       |
  1  |  0  |  10          |  2       |
  1  |  1  |  11          |  3       |
*/

/* GLOBALS */
// pins
const int LED_PINS[4]   = {2, 4, 7, 8}; 
const int INPUT_PINS[2] = {12, 13};
// output
volatile int current_output  = 0;
volatile int previous_output = 0;
// input
volatile bool A_state = 0; 
volatile bool B_state = 0; 

int getOutput(int AP, int BP){
  /* 
  getOutput()
  Takes the inputs (A, B) and returns the output
  in decimal.
  
  Args:
  AP: (1 or 0)
  - state of input A
  BP: (1 or 0)
  - state of input B

  Returns: (0, 1, 2, or 3)
  */
  return ((AP*2) + BP); 
}

void turnOffLEDs(){
  /*
  turnOffLEDs
  turn off all LEDs
  */
  for (int ii=0; ii<4; ii++){
    digitalWrite(LED_PINS[ii], LOW);
  }
}

void setup() {
  Serial.begin(9600); // baud rate
  Serial.println("Starting up...");

  // set up pins
  // set up LED PINS
  for (int ii=0; ii<4; ii++){
    pinMode(LED_PINS[ii], OUTPUT);
  }
  // set up input pins
  for (int ii=0; ii<2; ii++){
    pinMode(INPUT_PINS[ii], INPUT);
  }

  Serial.println("Arduino is ready!");

  Serial.println(" A | B | OUT "); // start table 
  Serial.print(" "); Serial.print(A_state); Serial.print(" | ");
  Serial.print(B_state); Serial.print(" | "); 
  Serial.println(current_output);
  digitalWrite(LED_PINS[current_output], HIGH);
}

void loop() {
  A_state = digitalRead(INPUT_PINS[0]);
  B_state = digitalRead(INPUT_PINS[1]);
  current_output = getOutput(A_state, B_state);

  if (current_output != previous_output){ // if output changes

    //print new table row
    Serial.print(" "); Serial.print(A_state); Serial.print(" | ");
    Serial.print(B_state); Serial.print(" | "); 
    Serial.println(current_output);

    // update LEDs 
    turnOffLEDs();
    digitalWrite(LED_PINS[current_output], HIGH);

    // update previous output
    previous_output = current_output; 
  }

}
