#include "solarCharge.hpp"

Ina238 *sensor;

int main (int argc, char **argv)
{
    bool batteryFullFlag = false;
    time_t currentTime;
    struct tm *localTime;
    setupTest();

    float voltage;

    while(voltage <= 2.71){
        time(&currentTime);
        localTime = localtime(&currentTime);
        
        voltage = connectAndSenseVoltage();
        //std::cout << "Alerts: " << std::hex << sensor->getAlerts() << std::endl;
        saveRecordedMesuremants(localTime, voltage);
        sleep(900);
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

void saveRecordedMesuremants(struct tm* localTime, float &voltage){
        std::ofstream file("testResults.txt", std::ios::app);
        file << "Time";
        if(localTime->tm_hour < 10){
            file << "0";
        }
        file << localTime->tm_hour << '.';
        if (localTime->tm_min < 10)
        {
            file << "0";
        }
        file << localTime->tm_min << ": " << voltage << std::endl;
        file.close();
}
