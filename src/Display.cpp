#include "Arduino.h"
#include "Display.h"

Display::Display(int dsPin, int shcpPin, int stcpPin) {
    _dsPin = dsPin;
    _shcpPin = shcpPin;
    _stcpPin = stcpPin;
    _value = "    ";
}

void Display::init() {
    DDRB = B1111;
    PORTB = B0000;

    pinMode(_dsPin, OUTPUT);
    pinMode(_stcpPin, OUTPUT);
    pinMode(_shcpPin, OUTPUT);
    for (int i = 0; i < 8; ++i) {
        digitalWrite(_dsPin, LOW);
        digitalWrite(_shcpPin, HIGH);
        digitalWrite(_shcpPin, LOW);
    }
    digitalWrite(_stcpPin, HIGH);
    digitalWrite(_stcpPin, LOW);
    setValue("0000");
}

int binV[] = {B11111100, B01100000, B11011010, B11110010, B01100110, B10110110, B10111110, B11100000, B11111110,
              B11110110, B11101110, B00111110, B10011100};
char strV[] = "0123456789";


int getMap(int v) {
    for (unsigned int i = 0; i < sizeof(strV); ++i) {
        if (strV[i] == v) {
            return binV[i];
        }
    }
    return B00000001;
}

void Display::tick() {
    _currentIndex = (_currentIndex + 1) % 4;
    char symbol = _value[_currentIndex];
    int binValue = getMap(symbol);
    for (int i = 0; i < 8; ++i) {
        if (binValue % 2 == 1) {
            digitalWrite(_dsPin, HIGH);
        } else {
            digitalWrite(_dsPin, LOW);
        }
        digitalWrite(_shcpPin, HIGH);
        digitalWrite(_shcpPin, LOW);


        binValue = binValue / 2;
    }
    PORTB = B1111;
    digitalWrite(_stcpPin, HIGH);
    digitalWrite(_stcpPin, LOW);
    PORTB = (~(1 << _currentIndex));
}

void Display::setValue(String value) {
    _value = value;
}