#include "Keyboard.h"

// IDE: Arduino/Genuino Micro

// autohotkey script:
//; control shift alt win-s
//^+!#s::
//	Process, Close, spssengine.exe
//	Process, Close, stats.exe
//Return

const int buttonPin  = 9;          // input pin for pushbutton (other end to GND)
const int switchPin1 = 10;         // input pin for one side of switch (middle goes to GND)
const int switchPin2 = 7;          // input pin for 2nd side of switch (middle goes to GND)

int previousButtonState;          // HIGH=released, LOW=pushed

void setup() {
  // make the pushButton pin an input with pull-up resistor enabled (so other end of button goes to GND):
  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(switchPin1, INPUT_PULLUP);
  pinMode(switchPin2, INPUT_PULLUP);
  previousButtonState = digitalRead(buttonPin);
  // initialize control over the keyboard:
  Keyboard.begin();
}

// message for sw1 - logout
void sendMessage1() {
  // CTRL-ALT-DEL:
  Keyboard.press(KEY_LEFT_CTRL);
  Keyboard.press(KEY_LEFT_ALT);
  Keyboard.press(KEY_DELETE);
  delay(100);
  Keyboard.releaseAll();
  //ALT-l:
  delay(2000);
  Keyboard.press(KEY_LEFT_ALT);
  Keyboard.press('l');
  Keyboard.releaseAll();
  // wait 1s so we don't have to debounce
  delay(1000);
}

void sendMessage2() {
  Keyboard.println("Nothing...");
}

// message sent if switch in middle position (sw1 and sw2 released)
void sendSPSSKillMessage() {
  // autohotkey script will react on control shift alt win-s
  Keyboard.press(KEY_LEFT_GUI);
  Keyboard.press(KEY_LEFT_CTRL);
  Keyboard.press(KEY_LEFT_SHIFT);
  Keyboard.press(KEY_LEFT_ALT);
  Keyboard.press('s');
  delay(100);
  Keyboard.releaseAll();
  // wait 1s more so we don't have to debounce
  delay(1000);
}

void loop() {
  // read the pushbutton:
  int buttonState = digitalRead(buttonPin);
  // if the button state has changed,
  if (buttonState != previousButtonState) {
    // save the current button state for comparison next time:
    previousButtonState = buttonState;
    // if it changed from HIGH to LOW it's pressed
    if (buttonState == LOW) {
      // which message to send?
      int sw1 = digitalRead(switchPin1);
      int sw2 = digitalRead(switchPin1);
      if ((sw1 == HIGH) && (sw2 == HIGH)) {
        sendSPSSKillMessage();
      } else if (sw1 == LOW) {
        sendMessage1();
      } else if (sw2 == LOW) {
        sendMessage2();
      }
    }
  }
}
