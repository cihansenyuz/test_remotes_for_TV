#include "irManager.hpp"

bool IrManager::edgeFlag = true;

IrManager::IrManager(int irPin){
    pinMode(irPin, INPUT);
    pullUpDnControl(irPin, PUD_DOWN);
    wiringPiISR(irPin, INT_EDGE_FALLING, &gpoiIntHandler);
}

int IrManager::waitForHeaderBits(){
    waitForEdge();
    auto headerStartTime = high_resolution_clock::now();
    waitForEdge();
    auto headerEndTime = high_resolution_clock::now();

    auto result = duration_cast<microseconds>(headerEndTime - headerStartTime);
    std::cout << "Header durition: " << result.count() << std::endl;
    return result.count();
}

bool IrManager::readBit(){
    while(digitalRead(irPin) == LOW){} // wait for high pulse which is the start of the bit
    auto dataStartTime = high_resolution_clock::now();
    waitForEdge();
    auto dataEndTime = high_resolution_clock::now();
    
    auto width = duration_cast<microseconds>(dataEndTime - dataStartTime);
    if(width.count() < 1500)
        return BIT0;
    else
        return BIT1;
}

void gpoiIntHandler(){
    IrManager::edgeFlag = false;
}

void IrManager::waitForEdge(){
    auto timeOut = high_resolution_clock::now();
    while(edgeFlag && (duration_cast<microseconds>(high_resolution_clock::now()
                        - timeOut)).count() < MAX_REMOTE_LATE_RESPONSE){}
    edgeFlag = true;    // reset the flag
}

bool IrManager::checkPowerKey(bool* data, int size){
    for(int i=0; i<size; i++){
        if(data[i] != powerKey[i])
            return false;
    }
    return true;
}

IrManager::~IrManager(){
    wiringPiISRStop(irPin);
}