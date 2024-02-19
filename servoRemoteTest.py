import RPi.GPIO as GPIO
import time

# Define GPIO pin for servo
servoPin = 33

# Define GPIO pin for input
inputPin = 12

# Set GPIO mode and configure the input pin
GPIO.setmode(GPIO.BOARD)
GPIO.setup(inputPin, GPIO.IN)

# Add event detection for falling edge on the input pin
GPIO.add_event_detect(inputPin, GPIO.FALLING)

# Set GPIO mode and configure the servo pin
GPIO.setup(servoPin, GPIO.OUT)

# Set PWM frequency and duty cycle
pwm = GPIO.PWM(servoPin, 50)
pwm.start(0)

# Initialize global variables
headerStartTime = 0
headerEndTime = 0
clickCounter = 0
errorCounter = 0

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

# Function to set the angle of the servo
def setAngle(angle):
    duty_cycle = angle / 18 + 2
    pwm.ChangeDutyCycle(duty_cycle)
    time.sleep(1)
    pwm.ChangeDutyCycle(0)

# Loop to move the servo back and forth
try:
    while True:
        headerTimeDifference = waitForHeaderBits()

        if headerTimeDifference > 7.9 and headerTimeDifference < 8.1:
            setAngle(30)
            time.sleep(1)

            clickCounter += 1
            print(f"Click counter: {clickCounter}, Signal Receive: OK")

        elif errorCounter >= 3:
            print(f"Click counter: {clickCounter}, Signal Receive: NOK")
            print("Signal lost 3 times and connection is interrupted, trying to reconnect...")
            break
        
        else:
            clickCounter += 1
            errorCounter += 1


except KeyboardInterrupt:
    pwm.stop()
    GPIO.cleanup()


