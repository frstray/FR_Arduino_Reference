
/*
 * Forest Ray
 * May 21, 2025
 * RAGU Lab internship 
 * 
 * Time to get some in-Struct-ion
 * 
 * Arduino Struct syntax organizes data into a single variable. 
 * This is useful for organizing groups of information in order to make code
 * easier to read and maintain. 
 * 
 * The general syntax for a struct:
 * struct struct_name {
 *  data_type_1 member_1;
 *  data_type_2 member_2;
 *  data_type_3 member_3;
 *  ...
 *  };
 *  
 *  declaring struct variables:
 *  struct user_defined_type variable_name 
 *  
 *  to access members of a struct:
 *  variable_name.member_name
 *  
 *  store value in struct:
 *  variable_name.member_name = value 
 *  
 *  struct variables can be passed to functions and returned by functions:
 *  
 *  struct struct_name function_name(struct struct_name variable_name){
 *   // can access members of the struct with variable_name.member_name
 *   struct struct_name new_variable_name;
 *   
 *   new_variable_name.member_name = <value>;
 *   
 *   return new_variable;
 *  }
 *  
 *  call the function:
 *  struct struct_name new_variable_name = function_name(struct_variable);
 *  
 */

// Let's make a struct 
struct dog {
  String dog_name;
  String breed;
  int    age;
};

// create a dog
struct dog spots;


void setup() {
  Serial.begin(9600); // 9600 baud rate 

  // Assign values to spots 
  spots.dog_name = "spots";
  spots.breed    = "dalmation";
  spots.age      = 2;

  Serial.print(spots.dog_name); Serial.print(", "); Serial.print(spots.breed); Serial.print(", "); Serial.println(spots.age);

}

void loop() {

}
