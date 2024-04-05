import RPi.GPIO as GPIO
import time
from INA238 import Ina238

class servoController():
    # Constructor
    def __init__(self, servoPin, inputPin):
        self.servoPin = servoPin
        self.inputPin = inputPin
        # Set GPIO mode and configure the input pin
        GPIO.setmode(GPIO.BOARD)
        GPIO.setup(self.inputPin, GPIO.IN)

        # Add event detection for falling edge on the input pin
        GPIO.add_event_detect(self.inputPin, GPIO.FALLING)

        # Set GPIO mode and configure the servo pin
        GPIO.setup(self.servoPin, GPIO.OUT)

        # Set PWM frequency and duty cycle
        self.pwm = GPIO.PWM(self.servoPin, 50)
        self.pwm.start(0)

        # Initialize global variables
        self.headerStartTime = 0
        self.headerEndTime = 0
        self.clickCounter = 0
        self.errorCounter = 0
        self.status = 'NOK'

    # Function to start GPIO
    def GPIO_start(self):
        GPIO.setmode(GPIO.BOARD)
        GPIO.setup(self.inputPin, GPIO.IN)
        GPIO.add_event_detect(self.inputPin, GPIO.FALLING)
        GPIO.setup(self.servoPin, GPIO.OUT)

    # Function to stop GPIO
    def GPIO_stop(self):
        GPIO.cleanup()

    # Function to wait for header bits and calculate header duration
    def waitForHeaderBits(self):

        # Wait for the first falling edge event on the input pin
        while 1:
            if GPIO.event_detected(self.inputPin):
                self.headerStartTime = time.perf_counter_ns()
                break
            else:
                pass

        # Wait for the second falling edge event on the input pin
        while 1:
            if GPIO.event_detected(self.inputPin):
                self.headerEndTime = time.perf_counter_ns()
                break
            else:
                pass
        
        # Calculate and print header duration in milliseconds
        result = (self.headerEndTime-self.headerStartTime)/1000000
        print(f"Header durition: {result:.2f} ms")
        return result

    # Function to set the angle of the servo
    def setAngle(self,angle):
        duty_cycle = angle / 18 + 2
        self.pwm.ChangeDutyCycle(duty_cycle)

    # Function to push the button
    def pushTheButton(self): 
        # Set the servo to 0 degrees and wait for header bits
        self.setAngle(0)
        headerTimeDifference = self.waitForHeaderBits()

        # If the header duration is between 7.9 and 8.1 milliseconds, set the servo to 30 degrees
        if headerTimeDifference > 7.9 and headerTimeDifference < 8.1:
            self.setAngle(30)

            # Increment the click counter and print a success message
            self.clickCounter += 1
            print(f"Click counter: {self.clickCounter}, Signal Receive: OK")         
            self.errorCounter = 0    
            
            # For log file to main file
            self.status = 'OK'
        
        elif self.errorCounter >= 3:
            # If the error counter is greater than or equal to 3, print an error message and break the loop
            print(f"Click counter: {self.clickCounter}, Signal Receive: NOK")
            print("Signal lost 3 times and connection is interrupted, try to reconnect...")
            self.GPIO_stop()

        else:
            # If the header duration is not between 7.9 and 8.1 milliseconds, increment the error counter
            print(f"Click counter: {self.clickCounter}, Signal Receive: NOK")
            self.clickCounter += 1
            self.errorCounter += 1
            
            # For log file to main file
            self.status = 'NOK'          
        
        # Wait for 1 second and then stop the servo
        time.sleep(1)
        self.GPIO_stop()
        self.GPIO_start()


