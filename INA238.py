import smbus2 as smbus
import time as time

BUS_NUMBER = 1          # board pin3 & pin5 is on I2C1
DEVICE_ADRESS = 0x40    # slave device adress
SHUNT_RES = 0.022
MAX_CURRENT = 0.05

DEVICE_ID = 0x3F        # slave device ID register
CONFIG = 0x00           # Configuration (CONFIG) Register
ADC_CONFIG = 0x01       # ADC Configuration (ADC_CONFIG) Register
SHUNT_CAL = 0x02        # Shunt Voltage Measurement
VBUS = 0x05             # Bus Voltage Measurement
DIETEMP = 0x06          # Temperature Measurement (DIETEMP) Register
CURRENT = 0x07          # Current result
POWER = 0x08            # Power result

'''
Reverses byte order to match INA238 transaction format
'''
def reverseWord(oldWord):
    newWord = oldWord & 0x00FF    # mask MSByte of oldWord    
    newWord = newWord << 8        # shift LSByte of newWord to MSByte   
    newWord |= (oldWord >> 8)     # shift MSByte of oldWord to LSByte and OR it to newWord
    return newWord 

class Ina238:
    def __init__(self, addr, busNum):
        self.bus = smbus.SMBus(busNum) 
        self.addr = addr
        self.current_lsb = 0

        '''
        CONFIG reg: 1R00 0000 00R0 RRRR
                                 ^ADCRANGE selection
                      ^--------^ADC conversiton delay
                    ^system reset
        '''
        # do a system reset
        self.bus.write_word_data(DEVICE_ADRESS, CONFIG, reverseWord(0x8000)) # system reset
        
        # set ADC conversion delay
        word = self.get16bitData(CONFIG)
        word &= (0xC07F << 6)   # clear bits 13-6
        word |= 0x40            # set ADC conversion delay to 2ms
        self.bus.write_word_data(DEVICE_ADRESS, CONFIG, reverseWord(word))
        
        # set ADC averaging
        word = self.get16bitData(ADC_CONFIG)
        word &= (0xFFF8)    # clear bits 3-0
        word |= 0x03        # set ADC averaging to 64
        self.bus.write_word_data(DEVICE_ADRESS, CONFIG, reverseWord(word))

    def get16bitData(self, reg):
        '''
        reads 16-bit word from I2C bus using given slave adress 'addr',
        and register 'reg' to be read. Performs bitwise operations to arrange byte order
        returns integer value of the word.
        '''
        word = reverseWord(self.bus.read_word_data(self.addr, reg))
        return word
    
    def setShuntCal(self, res, maxCur):
        '''
        CURRENT_LSB = Max Expected Current / 2^15
                    = 0.050 A / 32768

        Use Equation 1 for ADCRANGE = 0 (±163.84 mV). or ADCRANGE = 1 (±40.96 mV), the value of SHUNT_CAL must be
        multiplied by 4

        Eq. 1- SHUNT_CAL = 819.2 x 10^6 x CURRENT_LSB x R_SHUNT (0.022R)
        '''
        self.current_lsb = maxCur / 32768
        factor = 1
        while(self.current_lsb < 1):
            self.current_lsb *= 10
            factor *= 10
        self.current_lsb = 10 / factor
        shunt_cal_value = round(819200000 * self.current_lsb * res)
        self.bus.write_word_data(self.addr, SHUNT_CAL, reverseWord(shunt_cal_value))

    # get Device ID
    def deviceID(self):
        word = self.get16bitData(DEVICE_ID)
        print("Device ID: 0x{:02x}" .format(word))

    # get Die Temprature
    def temprature(self):
        time.sleep(0.05)
        word = self.get16bitData(DIETEMP)
        print("Die Temp:", (word>>4)*0.125, "C") # shift 4 bits cause bits 0-3 are reserved

    # get Bus Voltage
    def voltage(self):
        time.sleep(0.05)
        word = self.get16bitData(VBUS)
        print("Bus Voltage: {:.{}f}".format(word*0.003125, 2), 'V')

    # get Current
    def current(self):
        time.sleep(0.05)
        word = self.get16bitData(CURRENT)
        print("Current: {:.{}f}".format(word*self.current_lsb*1000, 3), 'mA')

ina = Ina238(DEVICE_ADRESS, BUS_NUMBER)
ina.setShuntCal(SHUNT_RES, MAX_CURRENT)

ina.deviceID()
ina.temprature()
ina.voltage()
ina.current()