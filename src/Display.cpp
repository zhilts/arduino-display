#include <Arduino.h>
#include "Display.h"

Display::Display(int dsPin, int shcpPin, int stcpPin) {
    _dsPin = dsPin;
    _shcpPin = shcpPin;
    _stcpPin = stcpPin;
    _value = "    ";
}

void Display::init() {
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
    _currentIndex = 3;
}

uint8_t binV[] = {B11111100, B01100000, B11011010, B11110010, B01100110, B10110110, B10111110, B11100000, B11111110,
                  B11110110, B00000000};
String strV = "0123456789 ";

uint8_t getDigitMap(char v) {
    int i = strV.indexOf(v);
    if (i == -1) {
        return B00000001;
    } else {
        return binV[i];
    }
}

uint8_t getSectionMap(int index) {
    return ~(1 << index);
}

uint16_t getMap(char v, int index) {
    uint8_t digit = getDigitMap(v);
    uint8_t section = getSectionMap(index);
    uint16_t result = (((uint16_t) section) << 8) | digit;
    return result;
}

void Display::tick() {
    _currentIndex = (_currentIndex + 1) % 4;
    char symbol = _value[3 - _currentIndex];
    uint16_t binValue = getMap(symbol, _currentIndex);
    for (int i = 0; i < 16; ++i) {
        if (binValue % 2 == 1) {
            digitalWrite(_dsPin, HIGH);
        } else {
            digitalWrite(_dsPin, LOW);
        }
        digitalWrite(_shcpPin, HIGH);
        digitalWrite(_shcpPin, LOW);


        binValue = binValue / 2;
    }
    digitalWrite(_stcpPin, HIGH);
    digitalWrite(_stcpPin, LOW);
}

void Display::setValue(String value) {
    String tempValue = value;
    while (tempValue.length() < 4) {
        tempValue = " " + tempValue;
    }
    _value = tempValue;
}