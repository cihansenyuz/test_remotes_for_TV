#include "irManager.hpp"

using namespace std::chrono;
//bool IrManager::edgeFlag = true;

IrManager::IrManager(int irPin){
    pinMode(irPin, INPUT);
    pullUpDnControl(irPin, PUD_UP);
   //wiringPiISR(irPin, INT_EDGE_FALLING, &gpoiIntHandler);
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

int IrManager::readBit(){
    while(digitalRead(irPin) == LOW){} // wait for high signal for the data bit
    auto dataStartTime = high_resolution_clock::now();
    while(digitalRead(irPin) == HIGH
            && (duration_cast<microseconds>(high_resolution_clock::now() - dataStartTime)).count()
            < 300000){}
    auto dataEndTime = high_resolution_clock::now();
    
    //waitForEdge();
    
    auto width = duration_cast<microseconds>(dataEndTime - dataStartTime);
    if(700 < width.count() && width.count() <= 1300)
        return 0;
    else if(1700 < width.count() && width.count() < 2300)
        return 1;
    else{
        std::cerr << "Absurd bit width: " << width.count() << std::endl; 
        return -1;
    }
}
/*
void gpoiIntHandler(){
    IrManager::edgeFlag = false;
}*/

void IrManager::waitForEdge(){
    auto timeOut = high_resolution_clock::now();
    while(digitalRead(irPin) == LOW){}
    while(digitalRead(irPin) == HIGH &&
            (duration_cast<microseconds>(high_resolution_clock::now() - timeOut)).count()
            < 300000){}
}

bool IrManager::checkPowerKey(int* data){
    for(int i=0; i<24; i++){
        if(data[i] != powerKey[i])
            return false;
    }
    return true;
}

IrManager::~IrManager(){
    wiringPiISRStop(irPin);
}