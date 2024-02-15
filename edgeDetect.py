import RPi.GPIO as GPIO
import time

inputPin = 3
GPIO.setmode(GPIO.BOARD)
GPIO.setup(inputPin, GPIO.IN)

flag = 0
startTime = 0
endTime = 0
flagStart = 0
startTimeStart = 0
endTimeStart = 0
first_time = 0
second_time = 0
start = 0
x = 0
checkpoint = 0

def fallingEdgeStart():
	global flagStart
	global startTimeStart
	global endTimeStart
	if flagStart == 0:
		startTimeStart = time.time()
		flagStart = 1
	else:
		endTimeStart = time.time()

def startCheck():
    GPIO.add_event_detect(inputPin, GPIO.FALLING)
    while 1:
        if GPIO.event_detected(inputPin):
            fallingEdgeStart()
            break
        else:
            pass
    print("1st edge detected!")

    while 1:
        if GPIO.event_detected(inputPin):
            fallingEdgeStart()
            break
        else:
            pass
    print("2nd edge detected!")
    print((endTimeStart-startTimeStart)*1000)
    return (endTimeStart-startTimeStart)*1000

def risingEdge():
    global startTime
    global endTime
    global checkpoint
    if checkpoint == 0:
        startTime = time.time()
        checkpoint = 1
    elif checkpoint == 1:
        endTime = time.time()
        checkpoint = 2
    elif checkpoint == 2:
        startTime = endTime
        endTime = time.time()

def bitCheck():
    while 1:
        if GPIO.event_detected(inputPin):
            risingEdge()
            break
        else:
            pass

    while 1:
        if GPIO.event_detected(inputPin):
            risingEdge()
            break
        else:
            pass
    
    return (endTime-startTime)*1000

def header():
    while 1:
        if GPIO.event_detected(inputPin):
            risingEdge()
            break
        else:
            pass
    return (endTime-startTime)*1000

try:
    counter = 0   
    difference = startCheck()
    
    if difference > 7.9 and difference < 8.2:
        GPIO.remove_event_detect(inputPin)
        GPIO.add_event_detect(inputPin, GPIO.RISING)
        
        time_diff = bitCheck()
        print(f"{counter} Time between first rising and second rising edge: ", time_diff)
        counter += 1
        while counter < 31:
            time_diff = header()
            print(f"{counter} Time between first rising and second rising edge: ", time_diff)
            counter += 1

    else:
        print("Please try again!")

except KeyboardInterrupt:
    GPIO.cleanup()
    print("\nProgram terminated by user\n")
    exit(0)
    