#include <Arduino.h>
#include "HID-Project.h"

#define PIN_BUTTON          13
#define PIN_UP              0
#define PIN_RIGHT           5
#define PIN_LEFT            7
#define PIN_DOWN            11

bool lastButtonState = false;
bool lastNorthState = false;
bool lastEastState = false;
bool lastWestState = false;
bool lastSouthState = false;

void setup() {
    pinMode(PIN_BUTTON, INPUT);
    pinMode(PIN_UP, INPUT);
    pinMode(PIN_RIGHT, INPUT);
    pinMode(PIN_LEFT, INPUT);
    pinMode(PIN_DOWN, INPUT);
    BootKeyboard.begin();
    BootKeyboard.releaseAll();
}

void loop() {
    bool currentState = digitalRead(PIN_BUTTON);
    if (currentState != lastButtonState) {
        Serial.println("Button changed");
        if (currentState) {
            BootKeyboard.press(KEY_F12);
        } else {
            BootKeyboard.release(KEY_F12);
        }
    }
    lastButtonState = currentState;
    currentState = digitalRead(PIN_UP);
    if (currentState != lastNorthState) {
        Serial.println("North changed");
        if (currentState) {
            BootKeyboard.press(KEY_UP);
        } else {
            BootKeyboard.release(KEY_UP);
        }
    }
    lastNorthState = currentState;
    currentState = digitalRead(PIN_RIGHT);
    if (currentState != lastEastState) {
        Serial.println("East changed");
        if (currentState) {
            BootKeyboard.press(KEY_RIGHT);
        } else {
            BootKeyboard.release(KEY_RIGHT);
        }
    }
    lastEastState = currentState;
    currentState = digitalRead(PIN_LEFT);
    if (currentState != lastWestState) {
        Serial.println("West changed");
        if (currentState) {
            BootKeyboard.press(KEY_LEFT);
        } else {
            BootKeyboard.release(KEY_LEFT);
        }
    }
    lastWestState = currentState;
    currentState = digitalRead(PIN_DOWN);
    if (currentState != lastSouthState) {
        Serial.println("South changed");
        if (currentState) {
            BootKeyboard.press(KEY_DOWN);
        } else {
            BootKeyboard.release(KEY_DOWN);
        }
    }
    lastSouthState = currentState;
}