//Teenys Keyboard
// Nunchuk for AWSD, SPACE and Q
// Key Buttons, for Arrow left, Arrow right, ESC, TAB, Enter
// 2 more buttons for full cursor Arrow up, Arrow down
// LED ligts up on button inputs


#include "Keyboard.h"
#include <NintendoExtensionCtrl.h>

const int led = 6; // LED pin

Nunchuk nchuk;

void setup() {
  Keyboard.begin();
  pinMode(led, OUTPUT);

  nchuk.begin();
  while (!nchuk.connect()) {
    Serial.println("Nunchuk not detected!");
    delay(1000);
  }

  // Joystick and button connections
  pinMode(3, INPUT_PULLUP); // Button connected to pin 3
  pinMode(4, INPUT_PULLUP); // Button connected to pin 4
  pinMode(5, INPUT_PULLUP); // Button connected to pin 5
  pinMode(7, INPUT_PULLUP); // Button connected to pin 7
  pinMode(8, INPUT_PULLUP); // Button connected to pin 8
  pinMode(9, INPUT_PULLUP); // Button connected to pin 9
  pinMode(10, INPUT_PULLUP); // Button connected to pin 10
  
}

void loop() {
  // Check button states
  int buttonState2 = digitalRead(3); // Button connected to pin 3
  int buttonState3 = digitalRead(4); // Button connected to pin 4
  int buttonState4 = digitalRead(5);  // digital read on pin 5
  int buttonState5 = digitalRead(7);  // digital read on pin7
  int buttonState6 = digitalRead(8);  // digital read on pin8
  int buttonState7 = digitalRead(9);  // digital read on pin9
  int buttonState8 = digitalRead(10);  // digital read on pin10

  // Update Nunchuk data
  boolean success = nchuk.update();

  if (!success) { // If the controller is not detected
    Serial.println("Controller disconnected!");
    delay(1000);
  } else {
    // Read joystick values
    int joyX = nchuk.joyX();
    int joyY = nchuk.joyY();

    // Map joystick values to keyboard commands
    if (joyX < 100) {
      Keyboard.press('a');
    } else if (joyX > 200) {
      Keyboard.press('d');
    } else {
      Keyboard.release('a');
      Keyboard.release('d');
    }

    if (joyY < 100) {
      Keyboard.press('s');
    } else if (joyY > 200) {
      Keyboard.press('w');
    } else {
      Keyboard.release('s');
      Keyboard.release('w');
    }

    // Read button states
    boolean zButton = nchuk.buttonZ();
    boolean cButton = nchuk.buttonC();

    // Send 'q' key if button Z is pressed
    if (zButton) {
      Keyboard.press('q'); // Press 'q' key
    } else {
      Keyboard.release('q'); // Release 'q' key
    }

    // Send space key if button C is pressed
    if (cButton) {
      Keyboard.press(' '); // Press space key
    } else {
      Keyboard.release(' '); // Release space key
    }
  }
  
  // Send left arrow key if buttonState2 is LOW
if (buttonState2 == LOW) {
  Keyboard.press(KEY_LEFT_ARROW);
  digitalWrite(led, HIGH); // Set LED to HIGH only when button is pressed
} else {
  Keyboard.release(KEY_LEFT_ARROW);
}

// Send right arrow key if buttonState3 is LOW
if (buttonState3 == LOW) {
  Keyboard.press(KEY_RIGHT_ARROW);
  digitalWrite(led, HIGH); // Set LED to HIGH only when button is pressed
} else {
  Keyboard.release(KEY_RIGHT_ARROW);
}

// Send ESC key if buttonState4 is LOW
if (buttonState4 == LOW) {
  Keyboard.press(KEY_UP_ARROW);
  digitalWrite(led, HIGH); // Set LED to HIGH only when button is pressed
} else {
  Keyboard.release(KEY_UP_ARROW);
}

// Send TAB key if buttonState5 is LOW
if (buttonState5 == LOW) {
  Keyboard.press(KEY_DOWN_ARROW);
  digitalWrite(led, HIGH); // Set LED to HIGH only when button is pressed
} else {
  Keyboard.release(KEY_DOWN_ARROW);
}

// Send RETURN key if buttonState6 is LOW
if (buttonState6 == LOW) {
  Keyboard.press(KEY_ESC);
  digitalWrite(led, HIGH); // Set LED to HIGH only when button is pressed
} else {
  Keyboard.release(KEY_ESC);
}

// Send TAB key if buttonState5 is LOW
if (buttonState7 == LOW) {
  Keyboard.press(KEY_TAB);
  digitalWrite(led, HIGH); // Set LED to HIGH only when button is pressed
} else {
  Keyboard.release(KEY_TAB);
}

// Send RETURN key if buttonState6 is LOW
if (buttonState8 == LOW) {
  Keyboard.press(KEY_RETURN);
  digitalWrite(led, HIGH); // Set LED to HIGH only when button is pressed
} else {
  Keyboard.release(KEY_RETURN);
}

// Set LED to LOW if none of the buttons are pressed
if (buttonState2 == HIGH && buttonState3 == HIGH && buttonState4 == HIGH && buttonState5 == HIGH && buttonState6 == HIGH && buttonState7 == HIGH && buttonState8 == HIGH) {
  digitalWrite(led, LOW);
}


  // Delay to avoid reading the buttons too quickly
  delay(50);
}
