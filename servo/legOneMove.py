#!/usr/bin/python

from RPIO import PWM
import time
import sys

servoGPIO=[17, 23,15]
VEL=0.2

print len(sys.argv)

def angleMap(angle):
    return int((round((1950.0/180.0),0)*angle)/10)*10+550

def movePos(art, pos):
    servo = PWM.Servo()
    print art
    servo.set_servo(art, angleMap(pos))
    time.sleep(VEL)


movePos(servoGPIO[int(sys.argv[1])], int(sys.argv[2]))
time.sleep(VEL)
