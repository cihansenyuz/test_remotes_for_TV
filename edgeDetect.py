import RPi.GPIO as GPIO
import time

inputPin = 12
GPIO.setmode(GPIO.BOARD)
GPIO.setup(inputPin, GPIO.IN)
GPIO.add_event_detect(inputPin, GPIO.FALLING)

headerStartTime = 0
headerEndTime = 0
dataEndTime = 0
firstBitflag = 0
bitCounter = 0

def waitForHeaderBits():
    global headerStartTime 
    global headerEndTime
    while 1:
        if GPIO.event_detected(inputPin):
            headerStartTime = time.perf_counter_ns()
            break
        else:
            pass
    while 1:
        if GPIO.event_detected(inputPin):
            headerEndTime = time.perf_counter_ns()
            break
        else:
            pass
    result = (headerEndTime-headerStartTime)/1000000
    print(f"Header durition: {result:.2f} ms")
    return result

def getPulseWidth():
    global flag
    global headerEndTime
    global dataEndTime
    if firstBitflag == 0:
        dataStartTime = headerEndTime
        dataEndTime = time.perf_counter_ns()
        firstBitflag = 1
    elif firstBitflag == 1:
        dataStartTime = dataEndTime
        dataEndTime = time.perf_counter_ns()
    return (dataEndTime-dataStartTime)/1000000

def bitCheck():
    dataWidth = 0
    GPIO.wait_for_edge(inputPin, GPIO.FALLING)
    dataWidth = getPulseWidth()
    print(f"Bit {bitCounter} durition: ", round(dataWidth, 2), " ms")
    if dataWidth > 2:
        return 1
    else:
        return 0

try:   
    headerTimeDifference = waitForHeaderBits()
    if headerTimeDifference > 7.9 and headerTimeDifference < 8.1:
        while bitCounter < 24:
            dataBit = bitCheck()
            print(f"Bit {bitCounter} is: ", dataBit)
            bitCounter += 1
    GPIO.cleanup()

except KeyboardInterrupt:
    GPIO.cleanup()
    print("\nProgram terminated by user\n")
    exit(0)