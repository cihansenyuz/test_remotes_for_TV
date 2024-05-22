#include "solarCharge.hpp"

Ina238 *sensor;

int main (int argc, char **argv)
{
    setupTest();

    while(true){
        std::cout << "Batt: ";
        connectAndSenseVoltage();
        std::cout << std::endl;
        sleep(10);
    }
    
    delete sensor;
    system("python3 ./graphTestResult.py --sc");
    return 0;
}

void setupTest(){
    if(wiringPiSetup())
        std::cerr << "wiringPi setup fail" << std::endl;

    sensor = new Ina238(DEVICE_ADDRESS, BUS_NUMBER);

    pinMode(RELAY_PIN, OUTPUT);
    digitalWrite(RELAY_PIN, HIGH);
    sleep(1);
}

float connectAndSenseVoltage(){
    digitalWrite(RELAY_PIN, LOW);
    float result = sensor->voltage();
    digitalWrite(RELAY_PIN, HIGH);
    delay(1);
    return result;
}

