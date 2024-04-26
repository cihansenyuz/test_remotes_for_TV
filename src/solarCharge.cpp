#include "solarCharge.hpp"

Ina238 *sensor;

int main (int argc, char **argv)
{
    bool batteryFullFlag = false;
    time_t currentTime;
    struct tm *localTime;
    setupTest();

    int i=5;
    while(!batteryFullFlag){
        time(&currentTime);
        localTime = localtime(&currentTime);
        float voltage = connectAndSenseVoltage();
        saveRecordedMesuremants(localTime, voltage);
        sleep(5);
        i--;
        if(!i)
            break;
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
}

float connectAndSenseVoltage(){
    digitalWrite(RELAY_PIN, LOW);
    delay(50);
    float temp = sensor->voltage();
    digitalWrite(RELAY_PIN, HIGH);
    delay(50);
    return temp;
}

void saveRecordedMesuremants(struct tm* localTime, float &voltage){
        std::ofstream file("testResults.txt", std::ios::app);
        file << "Time";
        if(localTime->tm_min < 10){
            file << "0";
        }
        file << localTime->tm_min << '.';
        if (localTime->tm_sec < 10)
        {
            file << "0";
        }
        file << localTime->tm_sec << ": " << voltage << std::endl;
        file.close();
}
