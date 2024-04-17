#include "wiringPi.h"

class ServoController
{
public:
    ServoController(int _servoPin);
    ~ServoController();
    void pressButton();
    void releaseButton();
    void setPosition(int pos);
private:
    int servoPin;
};