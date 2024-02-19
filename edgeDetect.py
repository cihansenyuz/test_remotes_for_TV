import RPi.GPIO as GPIO
import time

# Define GPIO pin for input
inputPin = 12

# Set GPIO mode and configure the input pin
GPIO.setmode(GPIO.BOARD)
GPIO.setup(inputPin, GPIO.IN)

# Add event detection for falling edge on the input pin
GPIO.add_event_detect(inputPin, GPIO.FALLING)

# Initialize global variables
headerStartTime = 0
headerEndTime = 0
dataEndTime = 0
firstBitflag = 0
bitCounter = 0

# Function to wait for header bits and calculate header duration
def waitForHeaderBits():
    global headerStartTime 
    global headerEndTime
    
    # Wait for the first falling edge event on the input pin
    while 1:
        if GPIO.event_detected(inputPin):
            headerStartTime = time.perf_counter_ns()
            break
        else:
            pass

    # Wait for the second falling edge event on the input pin
    while 1:
        if GPIO.event_detected(inputPin):
            headerEndTime = time.perf_counter_ns()
            break
        else:
            pass
    
    # Calculate and print header duration in milliseconds
    result = (headerEndTime-headerStartTime)/1000000
    print(f"Header durition: {result:.2f} ms")
    return result

# Function to get the pulse width of the data bits
def getPulseWidth():
    global firstBitflag
    global headerEndTime
    global dataEndTime
    
    # Calculate the pulse width based on the first or subsequent bit
    if firstBitflag == 0:
        dataStartTime = headerEndTime
        dataEndTime = time.perf_counter_ns()
        firstBitflag = 1
    elif firstBitflag == 1:
        dataStartTime = dataEndTime
        dataEndTime = time.perf_counter_ns()
    return (dataEndTime-dataStartTime)/1000000

# Function to check the duration of a bit and determine its value
def bitCheck():
    dataWidth = 0
    
    # Wait for the falling edge event on the input pin
    GPIO.wait_for_edge(inputPin, GPIO.FALLING)
    
    # Get the pulse width of the data bit
    dataWidth = getPulseWidth()
    print(f"Bit {bitCounter} durition: ", round(dataWidth, 2), " ms")
    
    # Check if the bit duration is greater than 2 ms and return the corresponding value
    if dataWidth > 2:
        return 1
    else:
        return 0

try:   
    # Main execution starts here
    headerTimeDifference = waitForHeaderBits()
    
    # Check if the header duration is within a specific range
    if headerTimeDifference > 7.9 and headerTimeDifference < 8.1:
        # Loop through 24 bits and print their values
        while bitCounter < 24:
            dataBit = bitCheck()
            print(f"Bit {bitCounter} is: ", dataBit)
            bitCounter += 1
    
    # Cleanup GPIO resources
    GPIO.cleanup()

except KeyboardInterrupt:
    # Cleanup GPIO resources if the program is terminated by the user
    GPIO.cleanup()
    print("\nProgram terminated by user\n")
    exit(0)
