/*
 * Forest Ray
 * May 21, 2025
 * RAGU Lab Internship 
 * 
 * Introduction to pointers
 */


// make a test integer 
int test_value = 3;

// create a pointer 
int *test_pointer;
/*
 * we could also say
 * int *test_pointer = &test_value
 * this would make the pointer point to the address of test_value
 */
 
void setup() {
  Serial.begin(9600); // baud rate 9600

  Serial.println("Let's print test_value and test_pointer");
  Serial.print("test_value = ");   Serial.println(test_value);
  Serial.print("test_pointer = "); Serial.println(*test_pointer); 

  // where do we want the pointer to point? 
  test_pointer = &test_value; // test_pointer now contains the address of test_value 
  Serial.println("\nAfter test_pointer = &test_value");
  Serial.print("test_value = ");   Serial.println(test_value);
  Serial.print("test_pointer = "); Serial.println(*test_pointer);

  // So, we can use a pointer to point the address of a variable
  // then, we can access that variable using the pointer 

  // What if we point to a pointer with a pointer?
  int *test_pointer_2; 
  int *test_pointer_3;
  Serial.println("Here are two unassigned pointers.");
  Serial.print("test_pointer_2 = "); Serial.println(*test_pointer_2);
  Serial.print("test_pointer_3 = "); Serial.println(*test_pointer_3);

  Serial.println("\ntest_pointer_3 = test_pointer_2");
  test_pointer_3 = test_pointer_2;
  Serial.print("test_pointer_2 = "); Serial.println(*test_pointer_2);
  Serial.print("test_pointer_3 = "); Serial.println(*test_pointer_3);

  Serial.println("\ntest_pointer_2 = &test_value");
  test_pointer_2 = &test_value;
  Serial.print("test_value = ");     Serial.println(test_value);
  Serial.print("test_pointer_2 = "); Serial.println(*test_pointer_2);
  Serial.print("test_pointer_3 = "); Serial.println(*test_pointer_3);

  // order still matters 
  Serial.println("\ntest_pointer_3 = test_pointer_2");
  test_pointer_3 = test_pointer_2;
  Serial.print("test_pointer_2 = "); Serial.println(*test_pointer_2);
  Serial.print("test_pointer_3 = "); Serial.println(*test_pointer_3);
  
}

void loop() {
  // put your main code here, to run repeatedly:

}
