#include "irManager.hpp"

IrManager::IrManager(int irPin){
    pinMode(irPin, INPUT);
    pullUpDnControl(irPin, PUD_DOWN);
    wiringPiISR(irPin, INT_EDGE_FALLING, &gpoiIntHandler);

    firstBitflag = false;
}

int IrManager::waitForHeaderBits(){
    waitForEdge();
    headerStartTime = std::chrono::high_resolution_clock::now();

    waitForEdge();
    headerEndTime = std::chrono::high_resolution_clock::now();

    auto result = std::chrono::duration_cast<std::chrono::microseconds>(headerEndTime - headerStartTime);
    std::cout << "Header durition: " << result.count() << std::endl;
    return result.count();
}

bool IrManager::readBit(){
    waitForEdge();
    if(!firstBitflag){
        dataStartTime = headerEndTime;
        dataEndTime = std::chrono::high_resolution_clock::now();
        firstBitflag = true;
    }
    else if(firstBitflag){
        dataStartTime = dataEndTime;
        dataEndTime = std::chrono::high_resolution_clock::now();
    }
    auto width = std::chrono::duration_cast<std::chrono::microseconds>(dataEndTime - dataStartTime);
    if(width.count() > 2000)
        return true;
    else
        return false;
}

bool IrManager::edgeFlag = true;

void gpoiIntHandler(){
    IrManager::edgeFlag = false;
}

void IrManager::waitForEdge(){
    while(edgeFlag){}
    edgeFlag = true;
}