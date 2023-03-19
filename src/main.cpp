#include <Arduino.h>
#include "HID-Project.h"
#include "Trill.h"

#define PIN_FIRE            13
#define PIN_MENU            1
#define PIN_UP              0
#define PIN_RIGHT           5
#define PIN_LEFT            7
#define PIN_DOWN            11

bool lastButtonState = false;
bool lastNorthState = false;
bool lastEastState = false;
bool lastWestState = false;
bool lastSouthState = false;
bool lastMenuState = false;
bool leftTouchActive = false;
bool rightTouchActive = false;

Trill trillSensorLeft;
Trill trillSensorRight;

void setup() {
    pinMode(PIN_FIRE, INPUT);
    pinMode(PIN_MENU, INPUT);
    pinMode(PIN_UP, INPUT);
    pinMode(PIN_RIGHT, INPUT);
    pinMode(PIN_LEFT, INPUT);
    pinMode(PIN_DOWN, INPUT);
    trillSensorLeft.setup(Trill::TRILL_SQUARE);
    trillSensorRight.setup(Trill::TRILL_SQUARE, 0x29);
    trillSensorLeft.setNoiseThreshold(80);
    trillSensorRight.setNoiseThreshold(80);
    BootKeyboard.begin();
    BootKeyboard.releaseAll();
}

void loop() {
    bool currentState = digitalRead(PIN_FIRE);
    if (currentState != lastButtonState) {
        Serial.println("Fire changed");
        if (currentState) {
            BootKeyboard.press(KEYPAD_5);
        } else {
            BootKeyboard.release(KEYPAD_5);
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
    currentState = digitalRead(PIN_MENU);
    if (currentState != lastMenuState) {
        Serial.println("Menu changed");
        if (currentState) {
            BootKeyboard.press(KEY_F12);
        } else {
            BootKeyboard.release(KEY_F12);
        }
    }
    lastMenuState = currentState;

    trillSensorLeft.read();
    if (trillSensorLeft.getNumTouches() > 0 || trillSensorLeft.getNumHorizontalTouches() > 0) {
        BootKeyboard.press(KEY_SPACE);
        leftTouchActive = true;
    } else if (leftTouchActive) {
        BootKeyboard.release(KEY_SPACE);
        leftTouchActive = false;
    }

    trillSensorRight.read();
    if (trillSensorRight.getNumTouches() > 0 || trillSensorRight.getNumHorizontalTouches() > 0) {
        BootKeyboard.press(KEY_ESC);
        rightTouchActive = true;
    } else if (rightTouchActive) {
        BootKeyboard.release(KEY_ESC);
        rightTouchActive = false;
    }
}