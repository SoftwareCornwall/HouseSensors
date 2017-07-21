#!/usr/bin/env python
import os
import time
import RPi.GPIO as GPIO
import datetime
now = datetime.datetime.now()
GPIO.setwarnings(False)


def mkdir_p(path):
    try:
        os.makedirs(path)
    except OSError as exc: # Python >2.5
        if exc.errno == errno.EEXIST and os.path.isdir(path):
            pass
        else: raise

#relation ship between raw number and liters
timesFactorForMin = 230
timesFactorForSec = 13800


HouseNumber = 21
Senser = "Rate Of Liquid Flow"

WaterDataLocation = "/home/pi/Desktop/HouseSensors/toxicCheese/House" + str(HouseNumber) + "/"+ str(HouseNumber) +"WaterData_" + (now.strftime("%Y_%m_%d")) + ".csv"
print (WaterDataLocation)
ivelocity = 0
icounter = 0
start = 0
end = 0

sMessageWater = ""

if os.path.isfile(WaterDataLocation) == False:
    mkdir_p(os.path.dirname(WaterDataLocation))
    Waterfile = open(WaterDataLocation,"w")
    Waterfile.close()

 
# handle the button event
def buttonEventHandler (pin):
    global icounter
    global start
    if start == 0:
        start = time.time()

    icounter += 1




# main function
def main():
    global icounter
    global start
    # tell the GPIO module that we want to use 
    # the chip's pin numbering scheme
    GPIO.setmode(GPIO.BCM)

    # setup pin 23 as an input
    # and set up pins 24 and 25 as outputs
    GPIO.setup(23,GPIO.IN)
    GPIO.setup(24,GPIO.OUT)
    GPIO.setup(25,GPIO.OUT)

    # tell the GPIO library to look out for an 
    # event on pin 23 and deal with it by calling 
    # the buttonEventHandler function
    GPIO.add_event_detect(23,GPIO.FALLING)
    GPIO.add_event_callback(23,buttonEventHandler) 




    while True:
        TimeDiff = time.time() - start
        if (TimeDiff < 1.01) and (TimeDiff > 0.99):
            sWaterMessage = str(now.strftime("%H:%M:%S")) + "," + str(icounter/timesFactorForMin)
            print (sWaterMessage)
            GPIO.cleanup()
            Waterfile = open(WaterDataLocation,"a")
            Waterfile.write(sWaterMessage)
            return(sWaterMessage)
            icounter = 0
            start = 0
            
            


    GPIO.cleanup()



icounter = 0
start = 0
print (main())
