#include "servoController.hpp"

ServoController::ServoController(int _servoPin) : servoPin(_servoPin) {
    pinMode(servoPin, PWM_OUTPUT);
    pwmSetMode(PWM_MODE_MS);
    // rasp pi 19.2MHz
    // 50Hz = 19.2MHz / 384 / 1000
    pwmSetClock(384);
    pwmSetRange(1000);
    
    releaseButton();
    delay(65);
}

void ServoController::pressButton(){
    pwmWrite(servoPin, 18);
    delay(65);
}

void ServoController::releaseButton(){
    pwmWrite(servoPin, 22);
}

void ServoController::setPosition(int pos){
    pwmWrite(servoPin, pos);
    delay(65);
}

ServoController::~ServoController(){
    releaseButton();
}