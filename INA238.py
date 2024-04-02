import smbus2 as smbus
import time as time

BUS_NUMBER = 1
bus = smbus.SMBus(BUS_NUMBER) # board pin3 & pin5 is on I2C1

DEVICE_ADRESS = 0x40    # slave device adress
DEVICE_ID = 0x3F        # slave device ID register
SHUNT_CAL = 0x02        # Shunt Voltage Measurement
VBUS = 0x05             # Bus Voltage Measurement
DIETEMP = 0x06          # Temperature Measurement (DIETEMP) Register
CURRENT = 0x07          # Current result
POWER = 0x08            # Power result

def get16bitData(addr, reg):
    '''
    reads 16-bit word from I2C bus using given slave adress 'addr',
    and register 'reg' to be read. Performs bitwise operations to arrange byte order
    returns integer value of the word.
    '''
    rawWord = bus.read_word_data(addr, reg)
    word = rawWord & 0x00FF         # mask MSByte of rawWord
    word = word << 8                # shift LSByte of word to MSByte
    word = word | (rawWord >> 8)    # shift MSByte of rawWord to LSByte and OR it to word
    return word

def setShuntCal(addr, reg, res, maxCur):
    '''
    CURRENT_LSB = Max Expected Current / 2^15
                = 0.050 A / 32768

    Use Equation 1 for ADCRANGE = 0 (±163.84 mV). or ADCRANGE = 1 (±40.96 mV), the value of SHUNT_CAL must be
    multiplied by 4

    Eq. 1- SHUNT_CAL = 819.2 x 10^6 x CURRENT_LSB x R_SHUNT (0.022R)
    '''
    current_lsb = maxCur / 32768
    factor = 1
    while current_lsb < 1:
        current_lsb *= 10
        factor *= 10
    current_lsb = 10.0 / factor
    shunt_cal = round(819200000 * current_lsb * res)

    reversed_shunt_cal = shunt_cal & 0x00FF        
    reversed_shunt_cal = reversed_shunt_cal << 8                
    reversed_shunt_cal = reversed_shunt_cal | (shunt_cal >> 8)    

    bus.write_word_data(addr, reg, reversed_shunt_cal)
    return current_lsb

current_lsb = setShuntCal(DEVICE_ADRESS, SHUNT_CAL, 0.022, 1) # shunt resistor=0.022R, max expected current=0.05A

# get Device ID
time.sleep(0.1)
word = get16bitData(DEVICE_ADRESS, DEVICE_ID)
print("device ID: 0x{:02x}" .format(word))

# get Die Temprature
time.sleep(0.1)
word = get16bitData(DEVICE_ADRESS, DIETEMP)
print("die temp:", (word>>4)*0.125, "C") # shift 4 bits cause bits 0-3 are reserved

# get VBUS
time.sleep(0.1)
word = get16bitData(DEVICE_ADRESS, VBUS)
print("VBus: {:.{}f}".format(word*0.003125, 2), 'V')

# get current
time.sleep(0.1)
word = get16bitData(DEVICE_ADRESS, CURRENT)
print(word)
print("Current: {:.{}f}".format(word*current_lsb, 3), 'A')