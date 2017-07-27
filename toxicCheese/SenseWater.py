#!/usr/bin/env python
import os 
import time
import RPi.GPIO as GPIO
from datetime import datetime
import requests
from uuid import getnode
import csv
import signal


#globals

url = "http://10.160.50.195/water.php"
#WaterFileLoc = "/home/pi/Desktop/WaterFlow.csv"
#relation ship between raw number and liters
timesFactorForMin = 230
timesFactorForSec = 13800
#Location of file storage, with name which is changing depending on date
HouseNumber = 21
WaterDataLocation = "/home/pi/Desktop/House" + str(HouseNumber) + "/"+ str(HouseNumber) +"WaterData.txt" # + str(datetime.now().strftime("%Y-%m-%d")) + ".csv"
WaterDataDirectory = "/home/pi/Desktop/House" + str(HouseNumber)

icounter = 0
start = 0

class TimeoutException(Exception):   # Custom exception class
    pass

def timeout_handler(signum, frame):   # Custom signal handler
    raise TimeoutException

def getMac():
    with open("/sys/class/net/wlan0/address", "r") as f:
        re = f.read()
        
    return re

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
    
    # Change the behavior of SIGALRM
    signal.signal(signal.SIGALRM, timeout_handler)

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
init()
while True:
    icounter = 0
    start = 0
    print ("fetching data")
    data = {'waterflow': getWaterFlow(), 
            'date': str(datetime.now().strftime("%Y-%m-%d")), 
            'timestamp': str(datetime.now().strftime("%H:%M:%S")),
            'mac' : str(getMac())
            }
    print ("done")
    # Start the timer. Once 5 seconds are over, a SIGALRM signal is sent.
    signal.alarm(5)    
    # This try/except loop ensures that 
    #   you'll catch TimeoutException when it's sent.
    try:
        print("posting data")
        if(os.path.isfile(WaterDataLocation) == True):
            print ("posting filedata")
            fileData = {}
            with open(WaterDataLocation, "r") as f:
                reader = csv.reader(f)
                for row in reader:
                    key = row[0]
                    fileData[key] = row[1:]
        print (data)
        r = requests.post(url, data)
        print (r)


    except TimeoutException:
        print ("To long to post data")
        continue # continue the for loop if function A takes more than 5 second

    except requests.exceptions.ConnectionError as e: 
        print("error connecting to server, writing to file")
        if(os.path.isfile(WaterDataLocation) == False):
            HumidFile = open(WaterDataLocation, 'w')
            HumidFile.close()
    
        HumidFile = open(WaterDataLocation, "a")
        HumidFile.write(str(data))
        HumidFile.write('\n')
        HumidFile.close()

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
    else:
        signal.alarm(0)
    # Reset the alarm    
    time.sleep(3) #58.99
    #Takes 1.01 seconds
