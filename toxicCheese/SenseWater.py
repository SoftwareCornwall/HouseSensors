#!/usr/bin/env python
import os 
import time
import RPi.GPIO as GPIO
from datetime import datetime
import requests
from uuid import getnode
import csv


#globals

url = "http://178.62.96.109/water.php"
#WaterFileLoc = "/home/pi/Desktop/WaterFlow.csv"
#relation ship between raw number and liters
timesFactorForMin = 230
timesFactorForSec = 13800
#Location of file storage, with name which is changing depending on date
HouseNumber = 21
WaterDataLocation = "/home/pi/Desktop/House" + str(HouseNumber) + "/"+ str(HouseNumber) +"WaterData.csv" # + str(datetime.now().strftime("%Y-%m-%d")) + ".csv"
WaterDataDirectory = "/home/pi/Desktop/House" + str(HouseNumber)

icounter = 0
start = 0


def getMac():
    address = getnode()
    h = iter(hex(address)[2:].zfill(12))
    return ":".join(i + next(h) for i in h)

def init():

    GPIO.setwarnings(False)
    # tell the GPIO module that we want to use 
    # the chip's pin numbering scheme
    GPIO.setmode(GPIO.BCM)

    #Creats a new file if one doesn't exsist
    if not os.path.exists(WaterDataDirectory):
        os.makedirs(WaterDataDirectory)
        
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
    smac = str(getMac())
    
# handle the button event
def buttonEventHandler (pin):
    global icounter
    global start
    if start == 0:
        start = time.time()

    icounter += 1

# main function
def getWaterFlow():
    global icounter
    global start
    while True:
        TimeDiff = time.time() - start
        if (TimeDiff < 1.01) and (TimeDiff > 0.99): #Needs to be range as time can never be exactly one
            #now = datetime.datetime.now()
            #timestamp
            water =  round(icounter/timesFactorForMin, 4)
            #print (water)
             #save to file
            return (water)
        
smac = str(getMac())
init()
while True:
    icounter = 0
    start = 0
    data = {'waterflow':  getWaterFlow(), 
            'date': str(datetime.now().strftime("%Y-%m-%d")), 
            'timestamp': str(datetime.now().strftime("%H:%M:%S")),
            'mac' : smac
            }
    print (data)
    try:
        print("posting data")
        print (os.path.isfile(WaterDataLocation))
        if(os.path.isfile(WaterDataLocation) == True):
            with open(WaterDataLocation, "r") as f:
                reader = csv.reader(f)
                fileData = {}
                for row in reader:
                    key = row[0]
                    fileData[key] = row[1:]
                    tr = requests.post(url, fileData)
                    print (fileData)
            os.remove(WaterDataLocation)
        r = requests.post(url, data)
        print (r)




    except requests.exceptions.ConnectionError as e: 
        print("error connecting to server {}, writing to file".format(e))
        if(os.path.isfile(WaterDataLocation) == False):
            with open(WaterDataLocation, "w") as f:
                writer = csv.DictWriter(f, data.keys())
                writer.writerow(data)
        else:
            with open(WaterDataLocation, "a") as f:
                writer = csv.DictWriter(f, data.keys()) 
                writer.writerow(data)

    except requests.exceptions.InvalidURL as e:
        print("invadlid url {}".format(e))
        print("exitting")
        break
    except requests.exceptions.HTTPError as e:
        print("HTTP error, exitting {} ".format(e))
        break
    except requests.exceptions.ConnectTimeout as e:
        print("HTTP error, exitting {} ".format(e))
        break    
    except:
        #e = sys.exc_info()[0]
        print ("unknown error")
        
        break
    time.sleep(58.99) #58.99
    #Takes 1.01 seconds
