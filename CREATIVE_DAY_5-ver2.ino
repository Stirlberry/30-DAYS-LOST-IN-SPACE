#include "Arduino.h" 
    
const byte RED_LED_1 = 11;      // pin controlling the cabin lights         // (RED)
const byte GREEN_LED_2 = 10;    // pin controlling the storage lights       // (GREEN)
const byte BLUE_LED_3 = 9;      // pin controlling the exterior lights      // (BLUE)
const byte WHITE_LED_4 = 6;     // pin controlling the corridor lights      // (WHITE)
const byte RED_LED_5 = 5;       // not nice doing it in the dark :)         // (RED)
const byte ORANGE_LED_6 = 3;    // pin controlling the air-lock lights      // (AMBER)
const byte GREEN_LED_7 = 12;    // pin controlling exta lights              // (GREEN) (pin 12 is only digitalWrite)

const byte SWITCH_1 = 7;          // pin connected to switch 1
const byte SWITCH_2 = 4;          // pin connected to switch 2
const byte SWITCH_3 = 2;          // pin connected to switch 3

// controlling brightness of lighting 
const byte RED_INTENSITY = 255;
const byte GREEN_INTENSITY = 255;
const byte BLUE_INTENSITY = 64;
const byte AMBER_INTENSITY = 128;
const byte WHITE_INTENSITY =32;

void setup() {
  // turning OFF on board (BUILT-IN LED)
  pinMode(LED_BUILTIN, OUTPUT);     // Access on-board LED
  digitalWrite(LED_BUILTIN, LOW);   // Turn off on-board LED

  // put your setup code here, to run once:         
  pinMode(RED_LED_1, OUTPUT);       // pin controlling the cabin lights       // (RED)
  pinMode(GREEN_LED_2, OUTPUT);     // pin controlling the storage lights     // (GREEN)
  pinMode(BLUE_LED_3, OUTPUT);      // pin controlling the exterior lights    // (BLUE)
  pinMode(WHITE_LED_4, OUTPUT);     // pin controlling the corridor lights    // (WHITE)
  pinMode(RED_LED_5, OUTPUT);       // pin controlling the bathroom lights    // (RED)
  pinMode(ORANGE_LED_6, OUTPUT);    // pin controlling the airlock lights     // (AMBER)
  pinMode(GREEN_LED_7, OUTPUT);     // pin controlling EXTRA_LIGHT            // (GREEN)

  // Configure the switch pins as INPUT pins
  pinMode(SWITCH_1, INPUT);           // pin connected to switch 1
  pinMode(SWITCH_2, INPUT);           // pin connected to switch 2 
  pinMode(SWITCH_3, INPUT);           // pin connected to switch 3 
}

void loop() {
  // Control lights based on switch positions

  // switch off all lights
  if (digitalRead(SWITCH_1) == LOW && digitalRead(SWITCH_2) == LOW && digitalRead(SWITCH_3) == LOW)
  {  
    analogWrite(RED_LED_1, 0);                // controlling the cabin lights
    analogWrite(GREEN_LED_2, 0);              // controlling the storage lights
    analogWrite(BLUE_LED_3, 0);               // controlling the exterior lights
    analogWrite(WHITE_LED_4, 0);              // pin controlling the corridor lights
    analogWrite(RED_LED_5, 0);                // pin controlling the toilet lights
    analogWrite(ORANGE_LED_6, 0);             // pin controlling the airlock lights
    digitalWrite(GREEN_LED_7, LOW);           // controlling EXTRA_LIGHTS
  } 

  // switch on light 1
  if (digitalRead(SWITCH_1) == HIGH && digitalRead(SWITCH_2) == LOW && digitalRead(SWITCH_3) == LOW)
  { 
    analogWrite(RED_LED_1, RED_INTENSITY);      // controlling the cabin lights
    analogWrite(GREEN_LED_2, 0);                // controlling the storage lights
    analogWrite(BLUE_LED_3, 0);                 // controlling the exterior lights
    analogWrite(WHITE_LED_4, 0);                // pin controlling the corridor lights
    analogWrite(RED_LED_5, 0);                  // pin controlling the toilet lights
    analogWrite(ORANGE_LED_6, 0);               // pin controlling the airlock lights     
    digitalWrite(GREEN_LED_7, LOW);             // controlling EXTRA_LIGHTS 
  } 
  
  // switch on light 2
  if (digitalRead(SWITCH_1) == LOW && digitalRead(SWITCH_2) == HIGH && digitalRead(SWITCH_3) == LOW)
  {
    analogWrite(RED_LED_1, 0);                    // controlling the cabin lights
    analogWrite(GREEN_LED_2, GREEN_INTENSITY);    // controlling the storage lights
    analogWrite(BLUE_LED_3, 0);                   // controlling the exterior lights           
    analogWrite(WHITE_LED_4, 0);                  // pin controlling the corridor lights
    analogWrite(RED_LED_5, 0);                    // pin controlling the toilet lights
    analogWrite(ORANGE_LED_6, 0);                 // pin controlling the airlock lights    
    digitalWrite(GREEN_LED_7, LOW);               // controlling EXTRA_LIGHTS
  }

  // switch on light 3
  if (digitalRead(SWITCH_1) == HIGH && digitalRead(SWITCH_2) == HIGH && digitalRead(SWITCH_3) == LOW)
  {
    analogWrite(RED_LED_1, 0);                    // controlling the cabin lights
    analogWrite(GREEN_LED_2, 0);                  // controlling the storage lights            
    analogWrite(BLUE_LED_3, BLUE_INTENSITY);      // controlling the exterior lights
    analogWrite(WHITE_LED_4, 0);                  // pin controlling the corridor lights
    analogWrite(RED_LED_5, 0);                    // pin controlling the toilet lights
    analogWrite(ORANGE_LED_6, 0);                 // pin controlling the airlock lights  
    digitalWrite(GREEN_LED_7, LOW);               // controlling EXTRA_LIGHTS 
  }

  // switch on light 4
  if (digitalRead(SWITCH_1) == LOW && digitalRead(SWITCH_2) == LOW && digitalRead(SWITCH_3) == HIGH)
  {
    analogWrite(RED_LED_1, 0);                    // controlling the cabin lights
    analogWrite(GREEN_LED_2, 0);                  // controlling the storage lights            
    analogWrite(BLUE_LED_3, 0);                   // controlling the exterior lights
    analogWrite(WHITE_LED_4, WHITE_INTENSITY);    // pin controlling the corridor lights
    analogWrite(RED_LED_5, 0);                    // pin controlling the toilet lights
    analogWrite(ORANGE_LED_6, 0);                 // pin controlling the airlock lights  
    digitalWrite(GREEN_LED_7, LOW);               // controlling EXTRA_LIGHTS 
  }

  // switch on light 5
  if (digitalRead(SWITCH_1) == HIGH && digitalRead(SWITCH_2) == LOW && digitalRead(SWITCH_3) == HIGH)
  {
    analogWrite(RED_LED_1, 0);                    // controlling the cabin lights
    analogWrite(GREEN_LED_2, 0);                  // controlling the storage lights          
    analogWrite(BLUE_LED_3, 0);                   // controlling the exterior lights
    analogWrite(WHITE_LED_4, 0);                  // pin controlling the corridor lights
    analogWrite(RED_LED_5, RED_INTENSITY);        // pin controlling the toilet lights
    analogWrite(ORANGE_LED_6, 0);                 // pin controlling the airlock lights       
    digitalWrite(GREEN_LED_7, LOW);               // controlling EXTRA_LIGHTS
  }

  // switch on light 6
  if (digitalRead(SWITCH_1) == LOW && digitalRead(SWITCH_2) == HIGH && digitalRead(SWITCH_3) == HIGH)
  {    
    analogWrite(RED_LED_1, 0);                    // controlling the cabin lights
    analogWrite(GREEN_LED_2, 0);                  // controlling the storage lights          
    analogWrite(BLUE_LED_3, 0);                   // controlling the exterior lights         
    analogWrite(WHITE_LED_4, 0);                  // pin controlling the corridor lights
    analogWrite(RED_LED_5, 0);                    // pin controlling the toilet lights
    analogWrite(ORANGE_LED_6, AMBER_INTENSITY);   // pin controlling the airlock lights   
    digitalWrite(GREEN_LED_7, LOW);               // controlling EXTRA_LIGHTS - NOT USED
  }

  // switch on light 7
  if (digitalRead(SWITCH_1) == HIGH && digitalRead(SWITCH_2) == HIGH && digitalRead(SWITCH_3) == HIGH)
  {
    analogWrite(RED_LED_1, 0);              // controlling the cabin lights         
    analogWrite(GREEN_LED_2, 0);            // controlling the storage lights       
    analogWrite(BLUE_LED_3, 0);             // controlling the exterior lights     
    analogWrite(WHITE_LED_4, 0);            // pin controlling the corridor lights  
    analogWrite(RED_LED_5, 0);              // pin controlling the toilet lights   
    analogWrite(ORANGE_LED_6, 0);           // pin controlling the airlock lights   
    digitalWrite(GREEN_LED_7, HIGH);        // controlling EXTRA_LIGHTS 
  }
} 