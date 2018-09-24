#include <Arduino.h>
#include "Display.h"

// register
int dsPin = 2; // data pin
int shcpPin = 4; // sync arduino -> internal
int stcpPin = 3; // sync internal -> external

Display display(dsPin, shcpPin, stcpPin);

void setup() {
    Serial.begin(9600);
    display.init();
}

void loop() {
    display.tick();
    display.setValue(String(millis() / 1000));
    delay(5);
}