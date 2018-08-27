#include <Display.h>
// register
int dsPin = 2; // data pin
int shcpPin = 4; // sync arduino -> internal
int stcpPin = 3; // sync internal -> external

int counter = 0;
int len = 2;

Display display(dsPin, shcpPin, stcpPin);

void setup() {
    display.init();
    display.setValue("1234");
    Serial.begin(9600);
}

void loop() {
    display.tick();
    delay(5);
}