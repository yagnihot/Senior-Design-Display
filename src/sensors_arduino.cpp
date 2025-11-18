// #include "sensors.hpp"


// /*
// ultrasonic, tilt, and light sensors. 
// */

// // ----------------------------------- GLOBAL LIGHT SENSOR VARIABLES & PINS --------------------------------//
// const int ldr_pin = A0;  
// int ldr_state = 2; // start out assuming dim, the in-between value


// // ---------------------------------- GLOBAL TILT VARIABLESS & PINS  ----------------------------------------
// const int tilt_left_pin = 4;
// const int tilt_back_pin = 2; 
// int tilt_right_pin = 3;
// int state = 0;

// //  100; // tilted to the back (4)
// //  010; // tilted to the left (2)
// //  001; // tilted to the right (1)
// //  101; // tilted to the back and right (5)
// //  110; // tilted to the back and left (6)
// //  000; // upright


// // ------------------------------------ GLOBAL ULTRASONIC VARIABLES & PINS ----------------------------------------
// const int trig_pin_left = 9; 
// const int echo_pin_left = 10; 
// const int trig_pin_right = 5;
// const int echo_pin_right = 6;

// int us_state_left = 0; 
// int us_state_right = 0; 
// int us_state = 0; // ?? 
// // we can also bit shift them by 4 and bitwise OR them with the other states to get one big state variable. 



// void setup() {
//   Serial.begin(9600);
  
//   pinMode(tilt_back_pin, INPUT);
//   pinMode(tilt_left_pin, INPUT);
//   pinMode(tilt_right_pin, INPUT);

//   pinMode(echo_pin_left, INPUT);
//   pinMode(trig_pin_left, OUTPUT);
//   digitalWrite(trig_pin_left, LOW);
//   pinMode(echo_pin_right, INPUT);
//   pinMode(trig_pin_right, OUTPUT);
//   digitalWrite(trig_pin_right, LOW);
  
// }


//     // gpio_isr_handler_add(GPIO_INPUT_IO_0, gpio_isr_handler, (void*) GPIO_INPUT_IO_0);


// void ldr(){

//   // ------------- LOCAL LIGHT SENSOR VARIABLES --------------------------//
  
//   float very_dim = 1.75; // voltage input value of LDR that indicates the surroundings are very dim
//   float bright = 1.2; // indicates surroundings are bright enough
//   float ldr_buffer = 0.05; // can be changed, allows for hysteresis


//   int ldr_value = 0; // value read from the ldr
//   float ldr_voltage = 0.00;
//   int ldr_state_next = 0;

//   ldr_value = analogRead(ldr_pin);
//   ldr_voltage = float(ldr_value) * 5.00 / 1023.00;
//   Serial.print("ldr voltage = ");
//   Serial.println(ldr_voltage);


//   if(ldr_state == 1){ // very dim
//     if(ldr_voltage < (bright - ldr_buffer)) {
//       ldr_state_next = 4; // bright
//     } else if(ldr_voltage < (very_dim - ldr_buffer)){
//       ldr_state_next = 2; // dim
//     } else{
//       ldr_state_next = 1; // very dim
//     }
    
//   } else if (ldr_state == 2) { // dim
//     if(ldr_voltage < (bright - ldr_buffer)) {
//       ldr_state_next = 4;
//     } else if (ldr_voltage > (very_dim + ldr_buffer)){
//       ldr_state_next = 1;
//     } else {
//       ldr_state_next = 2;
//     }
    
//   } else if(ldr_state == 4){ // bright
//     if(ldr_voltage > (very_dim + ldr_buffer)){
//       ldr_state_next = 1;
//     } else if(ldr_voltage > (bright + ldr_buffer)) {
//       ldr_state_next = 2;
//     } else{
//       ldr_state_next = 4;
//     }
//   }
  
//   ldr_state = ldr_state_next;
//   Serial.println();
//   Serial.print( "LDR state: ");
//   Serial.println(ldr_state);
//   if(ldr_state == 1){
//     Serial.println("Wow, it's very dark in here!");
//   } else if(ldr_state == 2) {
//     Serial.println("It's getting a little dark in here.");
//   } else if(ldr_state == 4) {
//     Serial.println("Conditions are bright enough.");
//   }
//   Serial.println();
   
// }





// void tilt() {
//   // global : state, pin numbers

//   int tilt_right_val = 0;
//   int tilt_left_val = 0;
//   int tilt_back_val = 0;
//   int next_state = 0;

//   int valid_states[] = {0b100, 0b010, 0b001, 0b101, 0b110, 0b000};
//   int invalid_states[] = {0b111, 0b011};
//   bool state_is_valid = true;
  
//    // read the value from the sensor:
//   tilt_right_val = digitalRead(tilt_right_pin);
//   tilt_left_val = digitalRead(tilt_left_pin);
//   tilt_back_val = digitalRead(tilt_back_pin);
//   delay(10);
  
//   // get different values for each sensor (1 or 0)
//   if(tilt_right_val == HIGH ) {
//     next_state = state | ( 1 << 0);  // walker tilted to the right 
//   }
//   else{
//     next_state = state & ~(1 << 0);
//   }
//   if(tilt_left_val == HIGH) {
//     next_state = next_state | ( 1 << 1);   // walker tilted to the left 
//   }
//   else {
//     next_state = next_state & ~(1 << 1);
//   }
//   if(tilt_back_val == HIGH) {
//     next_state = next_state | ( 1 << 2);   
//   }
//   else {
//     next_state = next_state & ~(1 << 2);
//   }

//   state = next_state; 
  
//   if(next_state == 0) {
//     Serial.println("Walker is upright.");
//   } else if(next_state == 1){
//     Serial.println("Walker has fallen to the right.");
//   } else if (next_state == 2){
//     Serial.println("Walker has fallen to the left.");
//   } else if (next_state == 3) {
//     Serial.println("Invalid state: Walker cannot be tilted to both left and right sides");
//   }else if (next_state == 4) {
//     Serial.println("Walker is tilted or has fallen to the back.");
//   }else if (next_state == 5) {
//     Serial.println("Walker is tilted to the back and right.");
//   }else if (next_state == 6) {
//     Serial.println("Walker is tilted to the back and left.");
//   }else if (next_state == 7) {
//     Serial.println("Uh oh! Walker is upside down!");
//   }


// }




// void ultrasonic(){

//   float timing_left = 0.0;
//   float distance_left = 0.0; 
//   float timing_right = 0.0;
//   float distance_right = 0.0; 
  
//   int next_us_state_left = 0; 
//   int next_us_state_right = 0;
//   // 000001: very close, left (1)
//   // 000010: close, left(2)
//   // 000100: far, left (4) 
  
  
//   const int a = 2; // buffers
//   const int b = 2;
//   const int c = 2;
  
//   digitalWrite(trig_pin_left, LOW);
//   delay(2);
//   digitalWrite(trig_pin_left, HIGH);
//   delay(10);
//   digitalWrite(trig_pin_left, LOW);

//   timing_left = pulseIn(echo_pin_left, HIGH);
//   distance_left = (timing_left * 0.034) /(2*2.54);
//   distance_left *= 10/8.85; // adjust for accuracy

//   digitalWrite(trig_pin_right, LOW);
//   delay(2);
//   digitalWrite(trig_pin_right, HIGH);
//   delay(10);
//   digitalWrite(trig_pin_right, LOW);
  
//   timing_right = pulseIn(echo_pin_right, HIGH);
//   distance_right = (timing_right * 0.034) /(2*2.54);
//   distance_right *= 10/8.85; // adjust for accuracy

//   //------------------- LEFT SIDE -------------------//
//   // beginning state
//   if(us_state_left == 0){
//     if(distance_left <= 12){
//       next_us_state_left = 1; // 1
//     } else if((distance_left > 12) && (distance_left < 24)){
//       next_us_state_left = 2; // 2
//     } else if(distance_left > 24){
//       next_us_state_left = 4; // 4
//     }
     
//   } 
//   // very close on left side
//   else if(us_state_left == 1){
//     if(distance_left > (24 + a)) {
//      next_us_state_left = 4;
//     } else if(distance_left > (12 + c)) {
//       next_us_state_left = 2;
//     } else {
//       next_us_state_left = 1;
//     }
//   }
//   // close on left side
//   else if(us_state_left == 2) {
//     if(distance_left > (24 + b)) {
//       next_us_state_left = 4;
//     } else if(distance_left < (12 - c)){
//       next_us_state_left = 1;
//     } else {
//       next_us_state_left = 2;
//     }
//   }
//   // far on left side
//   else if(us_state_left == 4) {
//     if (distance_left < (12-a)){
//       next_us_state_left = 1; // transition to very close
//     } else if (distance_left < (24 - b)){
//       next_us_state_left = 2; // transition to close
//     } else {
//       next_us_state_left = 4; // stay the same
//     }
    
//   }


// // ---------------- RIGHT SIDE ---------------- //
//   // beginning state
//   if(us_state_right == 0){
//     if(distance_right <= 12){
//       next_us_state_right = 1; // 1
//     } else if((distance_right > 12) && (distance_right < 24)){
//       next_us_state_right = 2; // 2
//     } else if(distance_right > 24){
//       next_us_state_right = 4; // 4
//     }
     
//   } 
//   // very close on right side
//   else if(us_state_right == 1){
//     if(distance_right > (24 + a)) {
//      next_us_state_right = 4;
//     } else if(distance_right > (12 + c)) {
//       next_us_state_right = 2;
//     } else {
//       next_us_state_right = 1;
//     }
//   }
//   // close on right side
//   else if(us_state_right == 2) {
//     if(distance_right > (24 + b)) {
//       next_us_state_right = 4;
//     } else if(distance_right < (12 - c)){
//       next_us_state_right = 1;
//     } else {
//       next_us_state_right = 2;
//     }
//   }
//   // far on right side
//   else if(us_state_right == 4) {
//     if (distance_right < (12-a)){
//       next_us_state_right = 1; // transition to very close
//     } else if (distance_right < (24 - b)){
//       next_us_state_right = 2; // transition to close
//     } else {
//       next_us_state_right = 4; // stay the same
//     }
    
//   }
  
//   us_state_left = next_us_state_left;
//   us_state_right = next_us_state_right;

//   Serial.print("Distance, left side: ");
//   Serial.print(distance_left);
//   Serial.print(" in.  | left ultrasonic state: ");
//   Serial.println(us_state_left);

//   Serial.print("Distance, right side: ");
//   Serial.print(distance_right);
//   Serial.print(" in. | right ultrasonic state: ");
//   Serial.println(us_state_right);

//   if(distance_right < 1) {
//     Serial.println("Ouch! Stop hitting me!");
//   }
//   if(distance_left < 1) {
//     Serial.println("Ouch! Stop hitting me!");
//   }  
// }
 

// // when the gold lead is tilted DOWN, the circuit closes. 
// void loop() {
  
//   Serial.println();

//   ldr();
//   tilt();
//   ultrasonic();
  
//   Serial.println();
//   delay(3000);

 
// }