#include "servoController.hpp"

ServoController::ServoController(int _servoPin) : servoPin(_servoPin) {
    pinMode(servoPin, PWM_OUTPUT);
    pwmSetMode(PWM_MODE_MS);
    // rasp pi 19.2MHz
    // 50Hz = 19.2MHz / 384 / 1000
    pwmSetClock(384);
    pwmSetRange(1000);
    
    releaseButton();
    delay(80);
}

void ServoController::pressButton(){
    pwmWrite(servoPin, 22);
    delay(100);
}

void ServoController::releaseButton(){
    pwmWrite(servoPin, 30);   // %3 duty cycle
    delay(80);
}

void ServoController::setPosition(int pos){
    pwmWrite(servoPin, pos);
    delay(80);
}

ServoController::~ServoController(){
    releaseButton();
}