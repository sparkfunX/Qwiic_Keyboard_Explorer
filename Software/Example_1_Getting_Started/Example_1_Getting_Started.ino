/*
  Basic Arduino USB Keyboard
  By: Nick Poole
  SparkFun Electronics
  Date: August 12th 2020
  License: This code is public domain but you buy me a beer if you use this and we meet someday (Beerware license).
  
  This example demonstrates how to use the Qwiic Keyboard Explorer as a simple USB keyboard. This sketch will
  also monitor the mode switch on the Keyboard Explorer and toggle between acting as a keyboard and acting as
  a serial device.

*/

#include <Keypad_Matrix.h> //https://github.com/nickgammon/Keypad_Matrix
#include "Keyboard.h"

// Declare how many keys are on the keyboard
const byte ROWS = 2;
const byte COLS = 7;

// Define how the keypad is laid out
const char keys[ROWS][COLS] = {
  {'1', '2','3','4','5','6','7'},
  {'a', 'b','c','d','e','f','g'}
};

// These are the pin declarations for the Qwiic Keyboard Explorer
const byte rowPins[ROWS] = {A0, A1}; 
const byte colPins[COLS] = {A2, 4, 5, 6, 7, 8, 9}; 

// Keep track of which mode we're currently in
boolean kbdMode = false;

// Create the Keypad object
Keypad_Matrix kpd = Keypad_Matrix( makeKeymap (keys), rowPins, colPins, ROWS, COLS );

// Key Press Handler
void keyDown (const char which)
  {
  if(kbdMode){
  Keyboard.press(which);  
  }else{
  SerialUSB.print (F("Key down: "));
  SerialUSB.println (which);
  }
  }

// Key Release Handler
void keyUp (const char which)
  {
  if(kbdMode){
  Keyboard.release(which);  
  }else{
  SerialUSB.print (F("Key up: "));
  SerialUSB.println (which);
  }
  }

// Check the mode switch position and change between USB-HID mode and Serial mode
void checkMode(){
  if(kbdMode){
    if(!digitalRead(A3)){
      kbdMode = false;
      Keyboard.end();
    }
  }else{
    if(digitalRead(A3)){
      kbdMode = true;
      Keyboard.begin();
    }    
  }
}

void setup()
{
  SerialUSB.begin(115200); // baud rate for Serial mode
  kpd.begin(); // initialise keyboard matrix
  kpd.setKeyDownHandler(keyDown); // declare keydown function
  kpd.setKeyUpHandler(keyUp); // declare keyup function
  pinMode(A3, INPUT_PULLUP); // initialize mode switch pin
}

void loop()
{
  kpd.scan(); // Get keyswitch statuses
  checkMode(); // Check mode switch
}
