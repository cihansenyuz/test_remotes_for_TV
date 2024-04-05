from INA238 import Ina238
from servoRemoteTest import servoController
import time

adress = 0x40
i2cPort = 1
shuntRes = 0.022
maxCur = 0.050
servoPin = 37
IRinputPin = 12

# Setup INA module with device adress and port number. Also, setup shunt resistor and max current
ina = Ina238(adress, i2cPort)
ina.setShuntCal(shuntRes, maxCur)

# Loop to move the servo back and forth
servo = servoController(servoPin, IRinputPin)

try:
    with open('Report.txt', 'a') as f:
        while True:
            servo.pushTheButton()
            if servo.status == 'OK':
                
                #log file
                f.write(f"Click counter: {servo.clickCounter} and OK \n")
                f.write(f"Battery Voltage: {ina.voltage()} V\n")
                f.write(f"Current: {ina.current()} mA\n")

            if servo.status == 'NOK':
                
                #log file
                f.write(f"Click counter: {servo.clickCounter} and NOK \n")
                f.write(f"Battery Voltage: {ina.voltage()} V\n")
                f.write(f"Current: {ina.current()} mA\n")
        
#If the user presses Ctrl+C, stop the PWM and clean up the GPIO
except KeyboardInterrupt:
    print("exception")
    servo.pwm.stop()
    servo.GPIO_stop()






