/*
  Arduino USB Keyboard with Macros
  By: Nick Poole
  SparkFun Electronics
  Date: August 12th 2020
  License: This code is public domain but you buy me a beer if you use this and we meet someday (Beerware license).
  
  This example demonstrates how to program simple macros by implementing a Chrome shortcuts macro pad. This sketch will
  also monitor the mode switch on the Keyboard Explorer and toggle between acting as a keyboard and acting as
  a serial device.

  Here is the keypad layout for this sketch:

  -------------------------------------------------------------------------------------
  |   Go To   |   Go To   |   Go To   |   Go To   |   Go To   |   Go To   |   Go To   |
  |   Tab 1   |   Tab 2   |   Tab 3   |   Tab 4   |   Tab 5   |   Tab 6   |   Tab 7   |
  |           |           |           |           |           |           |           |
  -------------------------------------------------------------------------------------
  |   Go      |  Refresh  |  Go       |    New    |   Close   |   Tab     |   Tab     |
  |   Back    |   Page    |  Forward  |    Tab    |    Tab    |   Left    |   Right   |
  |           |           |           |           |           |           |           |
  -------------------------------------------------------------------------------------
  
*/

#include <Keypad_Matrix.h> //https://github.com/nickgammon/Keypad_Matrix
#include "Keyboard.h"


// Declare how many keys are on the keyboard
const byte ROWS = 2;
const byte COLS = 7;

// Define how the keypad is laid out
const char keys[ROWS][COLS] = {
  {0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07},
  {0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E}
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
    switch(which){

      // Switch to Tab 1
      case 0x01:
          Keyboard.press(KEY_LEFT_CTRL);
          Keyboard.press('1');
          delay(100);
          Keyboard.releaseAll();
        break;
      // Switch to Tab 2
      case 0x02:
          Keyboard.press(KEY_LEFT_CTRL);
          Keyboard.press('2');
          delay(100);
          Keyboard.releaseAll();
        break;
      // Switch to Tab 3
      case 0x03:
          Keyboard.press(KEY_LEFT_CTRL);
          Keyboard.press('3');
          delay(100);
          Keyboard.releaseAll();
        break;
      // Switch to Tab 4
      case 0x04:
          Keyboard.press(KEY_LEFT_CTRL);
          Keyboard.press('4');
          delay(100);
          Keyboard.releaseAll();
        break;
      // Switch to Tab 5
      case 0x05:
          Keyboard.press(KEY_LEFT_CTRL);
          Keyboard.press('5');
          delay(100);
          Keyboard.releaseAll();
        break;
      // Switch to Tab 6
      case 0x06:
          Keyboard.press(KEY_LEFT_CTRL);
          Keyboard.press('6');
          delay(100);
          Keyboard.releaseAll();
        break;
      // Switch to Tab 7
      case 0x07:
          Keyboard.press(KEY_LEFT_CTRL);
          Keyboard.press('7');
          delay(100);
          Keyboard.releaseAll();
        break;
      // Back
      case 0x08:
          Keyboard.press(KEY_LEFT_ALT);
          Keyboard.press(KEY_LEFT_ARROW);
          delay(100);
          Keyboard.releaseAll();
        break;
      // Reload
      case 0x09:
          Keyboard.press(KEY_LEFT_CTRL);
          Keyboard.press('r');
          delay(100);
          Keyboard.releaseAll();
        break;
      // Forward
      case 0x0A:
          Keyboard.press(KEY_LEFT_ALT);
          Keyboard.press(KEY_RIGHT_ARROW);
          delay(100);
          Keyboard.releaseAll();
        break;
      // Open new tab
      case 0x0B:
          Keyboard.press(KEY_LEFT_CTRL);
          Keyboard.press('t');
          delay(100);
          Keyboard.releaseAll();
        break;
      // Close tab
      case 0x0C:
          Keyboard.press(KEY_LEFT_CTRL);
          Keyboard.press('w');
          delay(100);
          Keyboard.releaseAll();
        break;
      // Tab left
      case 0x0D:
          Keyboard.press(KEY_LEFT_CTRL);
          Keyboard.press(KEY_LEFT_SHIFT);
          Keyboard.press(KEY_TAB);
          delay(100);
          Keyboard.releaseAll();
        break;
      // Tab right
      case 0x0E:
          Keyboard.press(KEY_LEFT_CTRL);
          Keyboard.press(KEY_TAB);
          delay(100);
          Keyboard.releaseAll();
        break; 
        
      }
    }
  }

// Check the mode switch position and change between USB-HID mode and Serial mode
void checkMode(){
  if(kbdMode){
    if(!digitalRead(A3)){
      kbdMode = false;
      Keyboard.end();
      SerialUSB.println("Keyboard in USB Serial Mode");
    }
  }else{
    if(digitalRead(A3)){
      kbdMode = true;
      SerialUSB.println("Keyboard entering HID Mode");
      Keyboard.begin();
    }    
  }
}


void setup()
{
  SerialUSB.begin(115200); // baud rate for Serial mode
  kpd.begin(); // initialise keyboard matrix
  kpd.setKeyDownHandler(keyDown); // declare keydown function
  pinMode(A3, INPUT_PULLUP); // initialize mode switch pin
}

void loop()
{
  kpd.scan(); // Get keyswitch statuses
  checkMode(); // Check mode switch
}
