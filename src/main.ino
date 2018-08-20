// register
int dsPin = 2; // data pin
int shcpPin = 4; // sync arduino -> internal
int stcpPin = 3; // sync internal -> external

int counter = 0;
int len = 2;

void setup() {
    DDRB = B1111;
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
    Serial.begin(9600);
}

int currentSymbol = 4;
String value = " 777";
int binV[] = {B11111100, B01100000, B11011010, B11110010, B01100110, B10110110, B10111110, B11100000, B11111110, B11110110, B11101110, B00111110, B10011100};
char strV[] = "0123456789";
unsigned long lastRun = 0;
unsigned long lastRun2 = 0;

int getMap(int v) {
    for (int i = 0; i < sizeof(strV); ++i) {
        if (strV[i] == v) {
            return binV[i];
        }
    }
    return B00000001;
}

void tickDisplayRender() {
    currentSymbol = (currentSymbol + 1) % 4;
    char symbol = value[currentSymbol];
    int binValue = getMap(symbol);
    for (int i = 0; i < 8; ++i) {
        if (binValue % 2 == 1) {
            digitalWrite(dsPin, HIGH);
        } else {
            digitalWrite(dsPin, LOW);
        }
        digitalWrite(shcpPin, HIGH);
        digitalWrite(shcpPin, LOW);


        binValue = binValue / 2;
    }
    PORTB = B1111;
    digitalWrite(stcpPin, HIGH);
    digitalWrite(stcpPin, LOW);
    PORTB = (~(1 << currentSymbol));
}

void loop() {
    tickDisplayRender();
    delay(5);
}