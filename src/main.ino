// register
int dsPin = 2; // data pin
int shcpPin = 4; // sync arduino -> internal
int stcpPin = 3; // sync internal -> external

int counter = 0;
int len = 2;

void setup() {
    DDRB = B111111;
    PORTB = B0000;

    pinMode(dsPin, OUTPUT);
    pinMode(stcpPin, OUTPUT);
    pinMode(shcpPin, OUTPUT);
    for (int i = 0; i < 8; ++i) {
        digitalWrite(dsPin, LOW);
        digitalWrite(shcpPin, HIGH);
        digitalWrite(shcpPin, LOW);
        digitalWrite(stcpPin, HIGH);
        digitalWrite(stcpPin, LOW);
    }
}

void loop() {
    if (counter == 0) {
        digitalWrite(dsPin, HIGH);
    } else {
        digitalWrite(dsPin, LOW);
    }
    digitalWrite(shcpPin, HIGH);
    digitalWrite(shcpPin, LOW);

    digitalWrite(stcpPin, HIGH);
    digitalWrite(stcpPin, LOW);

    counter = (counter + 1) % len;
    delay(200);
}