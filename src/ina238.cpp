# include "ina238.hpp"

Ina238::Ina238(uint8_t addr, int busNum) {
    fd = wiringPiI2CSetup(addr);
    m_bus = busNum;
    m_addr = addr;
    m_currentLsb = 0;
    m_maxCurrent = 0;

    /*
    CONFIG reg: 1R00 0000 00R0 RRRR
                | |        | ^ADCRANGE selection
                | ^--------^ADC conversiton delay
                ^system reset
    */
    // do a system reset
    writeWordData(fd, CONFIG, 0x8000);
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
    if(!checkDevice())
        return;

    /*
    ADC_CONFIG reg: 1111 1011 0110 1000
                    |  | | ||  ||  ^-^ADC averaging
                    |  | | ||  |^--^Temp conversion time
                    |  | | |^--^Shunt voltage conversion time
                    |  | ^-^Bus voltage conversion time
                    ^--^ADC mode
    */
    uint16_t word = getWordData(ADC_CONFIG);
    word &= 0xFFF8;     // clear bits 2-0
    word |= 0x04;      // set ADC averaging to 128
    writeWordData(fd, ADC_CONFIG, word);
    word = getWordData(ADC_CONFIG);
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
}

uint16_t Ina238::reverseWord(uint16_t oldWord) {
    uint16_t newWord = oldWord & 0x00FF;    // mask MSByte of oldWord    
    newWord = newWord << 8;                // shift LSByte of newWord to MSByte   
    newWord |= (oldWord >> 8);             // shift MSByte of oldWord to LSByte and OR it to newWord
    return newWord;
}

uint16_t Ina238::getWordData(uint8_t reg) {
    uint16_t word = static_cast<uint16_t>(reverseWord(wiringPiI2CReadReg16(fd, reg)));
    return word;
}

void Ina238::writeWordData(int fd, uint8_t reg, uint16_t data){
    wiringPiI2CWriteReg16(fd, reg, reverseWord(data));
}

void Ina238::setShuntCal(double res, double maxCur) {
    m_maxCurrent = maxCur;
    m_currentLsb = maxCur / 32768000.0f;
    double factor = 1.0f;
    while (m_currentLsb < 1.0f) {
        m_currentLsb *= 10.0f;
        factor *= 10.0f;
    }
    m_currentLsb = 1000.0f / factor;
    uint16_t shuntCalValue = static_cast<uint16_t>(std::round(819200000.0f * m_currentLsb * res));
    writeWordData(fd, SHUNT_CAL, shuntCalValue);
}

bool Ina238::checkDevice() {
    uint16_t word = getWordData(DEVICE_ID);
    if(word == 0x2381){
        std::cout << "Device is ready" << std::endl;
        return true;
    }
    else{
        std::cerr << "Device is not responding!" << std::endl;
        return false;
    }
}

void Ina238::deviceID() {
    uint16_t word = getWordData(DEVICE_ID);
    std::cout << "Device ID: 0x" << std::hex << word << std::endl;
}

void Ina238::temperature() {
    uint16_t word = getWordData(DIETEMP);
    float temp = static_cast<float>(word >> 4) * 0.125f; // shift 4 bits cause bits 0-3 are reserved
    std::cout << "Die Temp: " << temp << " C" << std::endl;
}

float Ina238::voltage() {
    uint16_t word = getWordData(ADC_CONFIG);
    ConversionTime_t conversionSelection = static_cast<ConversionTime_t>((word >> 9) & 0x07);
    float conversionTime = 0;
    unsigned int delay = 0;
    switch (conversionSelection){
        case t50us:
            conversionTime = 50; break;
        case t84us:
            conversionTime = 84; break;
        case t150us:
            conversionTime = 150; break;
        case t280us:
            conversionTime = 280; break;
        case t540us:
            conversionTime = 540; break;
        case t1052us:
            conversionTime = 1052; break;
        case t2074us:
            conversionTime = 2074; break;
    }
    short averaging = (word & 0x07);
    if(averaging <= 3)
        averaging = pow(2, averaging) * pow(2, averaging);
    else
        averaging = pow(2, averaging) * 8;
    
    delay = 7.13 * conversionTime * averaging; // no less than (7,13 * ADC conversion time * averaging)
    std::this_thread::sleep_for(std::chrono::milliseconds(static_cast<int>(delay/1000))); 
    
    word = getWordData(VBUS);
    float batVoltage = static_cast<float>(word) * 0.003125f;
    printf("Bus Voltage: %f V\n", batVoltage);
    return batVoltage;
}

float Ina238::current() {
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
    uint16_t word = getWordData(CURRENT);
    double current = static_cast<double>(word) * m_currentLsb * 1000000.0f;
    if(current > m_maxCurrent)
        current = 0;
    std::cout << "Current: " << current << " uA" << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
    return current;
}

uint16_t Ina238::getAlerts(){
    uint16_t word = getWordData(DIAG_ALRT);
    return word;
}