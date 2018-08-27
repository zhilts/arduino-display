class Display {
public:
    Display(int dsPin, int shcpPin, int stcpPin);

    void init();

    void setValue(String value);

    void tick();

private:
    int _dsPin;
    int _shcpPin;
    int _stcpPin;
    String _value;
    int _currentIndex;
};