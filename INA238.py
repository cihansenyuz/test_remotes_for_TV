import smbus2 as smbus
import time as time

BUS_NUMBER = 1
bus = smbus.SMBus(BUS_NUMBER) # board pin3 & pin5 is on I2C1

DEVICE_ADRESS = 0x40    # slave device adress
DEVICE_ID = 0x3F        # slave device ID register
CONFIG = 0x00           # Configuration (CONFIG) Register
ADC_CONFIG = 0x01       # ADC Configuration (ADC_CONFIG) Register
SHUNT_CAL = 0x02        # Shunt Voltage Measurement
VBUS = 0x05             # Bus Voltage Measurement
DIETEMP = 0x06          # Temperature Measurement (DIETEMP) Register
CURRENT = 0x07          # Current result
POWER = 0x08            # Power result

def reverseWord(oldWord):
    newWord = oldWord & 0x00FF    # mask MSByte of oldWord    
    newWord = newWord << 8        # shift LSByte of newWord to MSByte   
    newWord |= (oldWord >> 8)     # shift MSByte of oldWord to LSByte and OR it to newWord
    return newWord   

def get16bitData(addr, reg):
    '''
    reads 16-bit word from I2C bus using given slave adress 'addr',
    and register 'reg' to be read. Performs bitwise operations to arrange byte order
    returns integer value of the word.
    '''
    word = reverseWord(bus.read_word_data(addr, reg))
    return word

def setShuntCal(res, maxCur):
    '''
    CURRENT_LSB = Max Expected Current / 2^15
                = 0.050 A / 32768

    Use Equation 1 for ADCRANGE = 0 (±163.84 mV). or ADCRANGE = 1 (±40.96 mV), the value of SHUNT_CAL must be
    multiplied by 4

    Eq. 1- SHUNT_CAL = 819.2 x 10^6 x CURRENT_LSB x R_SHUNT (0.022R)
    '''
    current_lsb = maxCur / 32768
    factor = 1
    while(current_lsb < 1):
        current_lsb *= 10
        factor *= 10
    current_lsb = 10 / factor
    shunt_cal_value = round(819200000 * current_lsb * res)
    bus.write_word_data(DEVICE_ADRESS, SHUNT_CAL, reverseWord(shunt_cal_value))
    return current_lsb

def initDevice():
    '''
    1R00 0000 00R0 RRRR
                 ^ADCRANGE selection
      ^--------^ADC conversiton delay
    ^system reset
    '''
    # do a system reset
    bus.write_word_data(DEVICE_ADRESS, CONFIG, reverseWord(0x8000)) # system reset
    
    # set ADC conversion delay
    word = get16bitData(DEVICE_ADRESS, CONFIG)
    word &= (0xC07F << 6)   # clear bits 13-6
    word |= 0x40            # set ADC conversion delay to 2ms
    bus.write_word_data(DEVICE_ADRESS, CONFIG, reverseWord(word))
    
    # set ADC averaging
    word = get16bitData(DEVICE_ADRESS, ADC_CONFIG)
    word &= (0xFFF8)    # clear bits 3-0
    word |= 0x03        # set ADC averaging to 64
    bus.write_word_data(DEVICE_ADRESS, CONFIG, reverseWord(word))

initDevice()
set_current_lsb = setShuntCal(0.022, 0.05) # shunt resistor=0.022R, max expected current=0.05A

# get Device ID
time.sleep(0.05)
word = get16bitData(DEVICE_ADRESS, DEVICE_ID)
print("Device ID: 0x{:02x}" .format(word))

# get Die Temprature
time.sleep(0.05)
word = get16bitData(DEVICE_ADRESS, DIETEMP)
print("Die Temp:", (word>>4)*0.125, "C") # shift 4 bits cause bits 0-3 are reserved

# get VBUS
time.sleep(0.05)
word = get16bitData(DEVICE_ADRESS, VBUS)
print("VBus: {:.{}f}".format(word*0.003125, 2), 'V')

# get current
time.sleep(0.05)
word = get16bitData(DEVICE_ADRESS, CURRENT)
print("Current: {:.{}f}".format(word*set_current_lsb*1000, 2), 'mA')