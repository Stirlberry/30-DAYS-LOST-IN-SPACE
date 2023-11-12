/*
 * 30 Days - Lost in Space
 * Creative Day 15 - Advanced Security Panel
*/

// Explicitly include Arduino.h
#include "Arduino.h"

// Include Keypad library
#include <Keypad.h>

// Our HERO keypad has 4 rows, each with 4 columns.
const byte ROWS = 4;
const byte COLS = 4;

const byte passwordLength = 4;                                    // PIN code is 4 button presses
char currentPassword[passwordLength] = { '0', '0', '0', '0' };  
const char intialPassword[passwordLength] = {'0', '0', '0', '0'}; // Initial password is four zeros.
bool passwordChanged = false;                                     // Password has not been changed 

// Define what characters will be returned by each button
const char BUTTONS[ROWS][COLS] = {
  { '1', '2', '3', 'A' },
  { '4', '5', '6', 'B' },
  { '7', '8', '9', 'C' },
  { '*', '0', '#', 'D' }
};

// Define row and column pins connected to the keypad
const byte ROW_PINS[ROWS] = { 5, 4, 3, 2 };
const byte COL_PINS[COLS] = { 6, 7, 8, 13 };  // NOTE wire moved from Day 13's sketch to pin 13

// Create our keypad object from the keypad configuration above
Keypad keypad = Keypad(makeKeymap(BUTTONS), ROW_PINS, COL_PINS, ROWS, COLS);

const byte BUZZER_PIN = 12;  // NOTE that pin 12 drives the buzzer now

const byte RED_PIN = 11;    // PWM pin controlling the red leg of our RGB LED
const byte GREEN_PIN = 10;  // PWM pin ccontrolling the green leg of our RGB LED
const byte BLUE_PIN = 9;    // PWM pin ccontrolling the blue leg of our RGB LED

// *****************************************************************************

void setup() {
  pinMode(RED_PIN, OUTPUT);
  pinMode(GREEN_PIN, OUTPUT);
  pinMode(BLUE_PIN, OUTPUT);

  // Since we start out "locked", we initially display a red color.
  RGB_LED(128, 0, 0);

  Serial.begin(9600);  // Begin monitoring via the serial monitor
  
  Serial.println();
  Serial.println("Hello ");

  // Only the option to change password is given after system is booted
  Serial.println("Please press * to set new password."); 
}

// *******************************************************************************

void loop() {

  char keyPress = keypad.getKey();  // Wait for a button press and save character

  // The '#' button unlocks our console
  if (keyPress == '#' && passwordChanged) {         // Button to access system. Only if initial password has been changed.
    giveInputFeedback();                            // Short beep with blue light
    
    // Function is called to check correct entry of password/pin and saved in 'access_allowed
    bool access_allowed = passwordVerification();   

    // Messages to user
    if (access_allowed) {
      Serial.println();
      Serial.println();
      Serial.println("Welcome, authorized user. You may now begin using the system.");
      Serial.println("System will lock in 1 minutes if no other key is pressed.");
      delay(60000);
      RGB_LED(128, 0, 0);
      Serial.println();
      Serial.println("System is locked!!");
      Serial.println("Press * to set new password or # to access the system.");
    } else {
      Serial.println("Access Denied.");
      Serial.println("\nPress * to enter new PIN or # to access the system.");
    }
  }

  // *****************************************************************************

  // The '*' allows the user to enter a new PIN after entering current PIN for security
  if (keyPress == '*') {        // Button to change password
    newPassword();              // calling newPassword function
  }
}

// *******************************************************************************

// Display a color by providing Red, Green and Blue intensities (0-255)
void RGB_LED(byte red_intensity, byte green_intensity, byte blue_intensity) {
  analogWrite(RED_PIN, red_intensity);      // Set red LED intensity using PWM
  analogWrite(GREEN_PIN, green_intensity);  // Set green LED intensity using PWM
  analogWrite(BLUE_PIN, blue_intensity);    // Set blue LED intensity using PWM
}

/*
 * NOTE:
 * Both the PWM functions and tone() functions use some of the same HERO hardware
 * for their functions.  If the RGB LED is on while a tone is played it will flicker
 * or diplay other colors.  Because of this, we turn off the LED while a tone is
 * being played and restore it immediately afterwards.
 */

// *******************************************************************************

// A recognized button was pressed.  Give short beep and blue LED
void giveInputFeedback() {
  RGB_LED(0, 0, 0);  // Turn off LED while playing tone
  tone(BUZZER_PIN, 880, 200);
  delay(200);               // Delay while tone is playing because tone() returns immediately
  RGB_LED(0, 0, 128);  // Restore blue LED
}

// ******************************************************************************

// A matching PIN has been entered.
// Play TADA! sound and display green LED
void giveSuccessFeedback() {
  RGB_LED(0, 0, 0);  // Turn off LED while playing tone
  tone(BUZZER_PIN, 300, 200);
  delay(200);  // Delay while tone is playing because tone() returns immediately

  tone(BUZZER_PIN, 500, 500);
  delay(500);  // Delay while tone is playing because tone() returns immediately
  RGB_LED(0, 128, 0); // Display green LED
}

// *****************************************************************************

// New PIN has been accepted.
// Play TADA! sound and display red LED
void giveSuccesspasswordChanged() {
  RGB_LED(0, 0, 0);  // Turn off LED while playing tone
  tone(BUZZER_PIN, 300, 200);
  delay(200);  // Delay while tone is playing because tone() returns immediately

  tone(BUZZER_PIN, 500, 500);
  delay(500);  // Delay while tone is playing because tone() returns immediately
  RGB_LED(128, 0, 0); // Display green LED
}

// *****************************************************************************

// Bad PIN entered.  Play descending tone and display red LED
void giveErrorFeedback() {
  RGB_LED(0, 0, 0);  // Turn off LED while playing tone
  tone(BUZZER_PIN, 300, 200);
  delay(200);  // Delay while tone is playing because tone() returns immediately

  tone(BUZZER_PIN, 200, 500);  // Frequency = 200Hz, Duration = 200ms
  delay(500);  // Delay while tone is playing because tone() returns immediately
  RGB_LED(128, 0, 0);  // Display red LED
}

// *****************************************************************************

// Password verfication function
bool passwordVerification() {

  char keyPress;
  char enteredPassword[passwordLength];

  Serial.println("Enter current password.");
  
  // save entered password
  for(int i = 0; i < passwordLength; i++) {

    while(!(keyPress = keypad.getKey())) {
    // wait indefinitely for keypad input of any kind
    } 

    giveInputFeedback();
    
    enteredPassword[i] = keyPress;
 
    Serial.print("*");    // print a phantom character for a successful keystroke
  }

  // Check entered password against current password
  for(int i = 0; i < passwordLength; i++) {
    if(enteredPassword[i] != currentPassword[i]) {
      giveErrorFeedback();
      Serial.println();
      Serial.println("WRONG PASSWORD");
      Serial.println("ACCESS DENIED!");
      Serial.println("System is locked!");

      delay(500);
      return false;      // failed
    }
    else {
      giveSuccessFeedback();
      return true;    //  succeeded
    }
  }
}

// *****************************************************************************

void newPassword() {
  giveInputFeedback();                  // Short beep with blue light
  bool access_allowed = passwordVerification();  // Have user enter PIN to allow access

  if (access_allowed) {
    RGB_LED(128, 80, 0);  // Display yellow LED while entering a NEW PIN
    Serial.println();
    Serial.println("\nWelcome, authorized user. Please Enter a new password: ");

    // Use a for() loop that runs once for each PIN character.  Each character read
    // replaces a character in our original PIN.
    for (int i = 0; i < passwordLength; i++) {
      currentPassword[i] = keypad.waitForKey();  // replace PIN character with new character
      // NOTE: After the LAST button press we will give Success feedback, but up to the
      //       last character we simply give input feedback.  Since Array indices start
      //       at 0, this if() statement will be true for all but the LAST character of
      //       the new PIN.
    
      if (i < (passwordLength - 1)) {
        giveInputFeedback();
        RGB_LED(128, 92, 0);  // override color
      }
      Serial.print("*");
    }

    Serial.println();  // add new line after last asterisk so next message is on next line
    Serial.println("PIN Successfully Changed!");
    Serial.println("\nPress * to enter new PIN or # to access the system.");
    passwordChanged = true;
    giveSuccesspasswordChanged();  // TADA sound and green light for successful PIN change
  } 
  else {
    Serial.println("Cannot change PIN without entering current PIN first.");
    Serial.println("\nPress * to enter new PIN or # to access the system.");
  }
}

// *****************************************************************************
