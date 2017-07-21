#!/usr/bin/env python
import os
import time
import RPi.GPIO as GPIO
import datetime

now = datetime.datetime.now()
GPIO.setwarnings(False)
# tell the GPIO module that we want to use 
# the chip's pin numbering scheme
GPIO.setmode(GPIO.BCM)

print ("Hello")

#relation ship between raw number and liters
timesFactorForMin = 230
timesFactorForSec = 13800


HouseNumber = 21
Senser = "Rate Of Liquid Flow"

WaterDataLocation = "/home/pi/Desktop/HouseSensors/toxicCheese/House" + str(HouseNumber) + "/"+ str(HouseNumber) +"WaterData_" + (now.strftime("%Y_%m_%d")) + ".csv"
WaterDataDirectory = "/home/pi/Desktop/HouseSensors/toxicCheese/House" + str(HouseNumber)
 
if not os.path.exists(WaterDataDirectory):
    os.makedirs(WaterDataDirectory)


icounter = 0
start = 0
#end = 0

sMessageWater = ""




 
# handle the button event
def buttonEventHandler (pin):
    global icounter
    global start
    if start == 0:
        start = time.time()

    icounter += 1


def StartUp():
    #setup pin 23 as an input
    # and set up pins 24 and 25 as outputs
    GPIO.setup(23,GPIO.IN)
    GPIO.setup(24,GPIO.OUT)
    GPIO.setup(25,GPIO.OUT)

    # tell the GPIO library to look out for an 
    # event on pin 23 and deal with it by calling 
    # the buttonEventHandler function
    GPIO.add_event_detect(23,GPIO.FALLING)
    GPIO.add_event_callback(23,buttonEventHandler) 
    


# main function
def main():
    global icounter
    global start
    
    while True:
        #time.sleep(1)
        TimeDiff = time.time() - start
        if (TimeDiff < 1.01) and (TimeDiff > 0.99):
            now = datetime.datetime.now()
            sWaterMessage = str(now.strftime("%H:%M:%S")) + "," + str(round(icounter/timesFactorForMin, 4)) + "\n"
            #print (sWaterMessage)
            Waterfile = open(WaterDataLocation,"a")
            Waterfile.write(sWaterMessage)
            Waterfile.close()
            return (sWaterMessage)


StartUp()
while True:
    icounter = 0
    start = 0
    print (main())
    time.sleep(1)
