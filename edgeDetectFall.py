import RPi.GPIO as GPIO
import time

inputPin = 12
GPIO.setmode(GPIO.BOARD)
GPIO.setup(inputPin, GPIO.IN)
GPIO.add_event_detect(inputPin, GPIO.FALLING)

headerStartTime = 0
headerEndTime = 0
dataEndTime = 0
flag = 0
counter = 0

def waitForHeaderBits():
    global headerStartTime 
    global headerEndTime
    while 1:
        if GPIO.event_detected(inputPin):
            headerStartTime = time.perf_counter()
            break
        else:
            pass
    while 1:
        if GPIO.event_detected(inputPin):
            headerEndTime = time.perf_counter()
            break
        else:
            pass
    result = (headerEndTime-headerStartTime)*1000
    print(f"Header durition: {result:.2f} ms")
    return result

def getPulseWidth():
    global flag
    global headerEndTime
    global dataEndTime
    if flag == 0:
        dataStartTime = headerEndTime
        dataEndTime = time.perf_counter()
        flag = 1
    elif flag == 1:
        dataStartTime = dataEndTime
        dataEndTime = time.perf_counter()
    return (dataEndTime-dataStartTime)*1000

def bitCheck():
    dataWidth = 0
    while 1:
        if GPIO.event_detected(inputPin):
            dataWidth = getPulseWidth()
            break
        else:
            pass
    return dataWidth

try:   
    headerTimeDifference = waitForHeaderBits()
    if headerTimeDifference > 7.9 and headerTimeDifference < 8.1:
        while counter < 24:
            dataTimeDifference = bitCheck()
            print(f"Bit {counter} durition: ", round(dataTimeDifference, 2), " ms")
            counter += 1

except KeyboardInterrupt:
    GPIO.cleanup()
    print("\nProgram terminated by user\n")
    exit(0)

