#include "wiringPi.h"

class ServoController
{
public:
    ServoController(int _servoPin);
    void pushButton();
    void releaseButton();
private:
    int servoPin;
};