#include "servoController.hpp"

ServoController::ServoController(int _servoPin) : servoPin(_servoPin) {
    pinMode(servoPin, PWM_OUTPUT);
    pwmSetMode(PWM_MODE_MS);
    // rasp pi 19.2MHz
    // 50Hz = 19.2MHz / 384 / 1000
    pwmSetClock(384);
    pwmSetRange(1000);
}

void ServoController::pushButton(){
    pwmWrite(servoPin, 22);
}

void ServoController::releaseButton(){
    pwmWrite(servoPin, 30);   // %3 duty cycle
}