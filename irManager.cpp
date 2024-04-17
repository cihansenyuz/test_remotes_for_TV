#include "irManager.hpp"

bool IrManager::edgeFlag = true;

IrManager::IrManager(int irPin){
    pinMode(irPin, INPUT);
    pullUpDnControl(irPin, PUD_DOWN);
    wiringPiISR(irPin, INT_EDGE_FALLING, &gpoiIntHandler);
}

int IrManager::waitForHeaderBits(){
    waitForInterrupt(irPin, -1);
    headerStartTime = std::chrono::high_resolution_clock::now();
    
    waitForInterrupt(irPin, -1);
    headerEndTime = std::chrono::high_resolution_clock::now();

    auto result = std::chrono::duration_cast<std::chrono::microseconds>(headerEndTime - headerStartTime);
    std::cout << "Header durition: " << result.count() << std::endl;    
    firstBitflag = true;
    return result.count();
}

bool IrManager::readBit(){
    waitForInterrupt(irPin, -1);
    if(firstBitflag){
        dataStartTime = headerEndTime;
        dataEndTime = std::chrono::high_resolution_clock::now();
        firstBitflag = false;
    }
    else{
        dataStartTime = dataEndTime;
        dataEndTime = std::chrono::high_resolution_clock::now();
    }
    auto width = std::chrono::duration_cast<std::chrono::microseconds>(dataEndTime - dataStartTime);
    std::cout << width.count() << " ";
    if(width.count() > 2000)
        return true;
    else
        return false;
}

void gpoiIntHandler(){
    IrManager::edgeFlag = false;
}

void IrManager::waitForEdge(){
    while(edgeFlag){}
    edgeFlag = true;
}

bool IrManager::checkPowerKey(bool* data){
    for(int i=0; i<24; i++){
        if(data[i] != powerKey[i])
            return false;
    }
    return true;
}

IrManager::~IrManager(){
    wiringPiISRStop(irPin);
}