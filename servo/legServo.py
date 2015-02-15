#!/usr/bin/python

from RPIO import PWM
import time
import sys

servoGPIO=[17, 23,15]
VEL=0.1

if len(sys.argv) > 1:
    times=int(sys.argv[1])
else:
    times=1

def angleMap(angle):
    return int((round((1950.0/180.0),0)*angle)/10)*10+550

def movePos(art, pos):
    servo = PWM.Servo()
    print art
    servo.set_servo(art, angleMap(pos))
    time.sleep(VEL)


for i in range(times):
    movePos(servoGPIO[2], 130)
    time.sleep(VEL)
    time.sleep(VEL)
    movePos(servoGPIO[1], 70)
    time.sleep(VEL)
    time.sleep(VEL)
    movePos(servoGPIO[0], 90)
    time.sleep(VEL)
    time.sleep(VEL)
    time.sleep(VEL)
    movePos(servoGPIO[1], 40)
    time.sleep(VEL)
    time.sleep(VEL)
    time.sleep(VEL)
    movePos(servoGPIO[0], 150)
    time.sleep(VEL)
    time.sleep(VEL)
    time.sleep(VEL)

time.sleep(VEL)
time.sleep(VEL)
movePos(servoGPIO[1],180)
time.sleep(VEL)
time.sleep(VEL)
movePos(servoGPIO[2],180)
time.sleep(VEL)
time.sleep(VEL)
movePos(servoGPIO[0],90)
time.sleep(VEL)
time.sleep(VEL)
