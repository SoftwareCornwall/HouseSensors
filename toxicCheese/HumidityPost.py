import requests
import os
from sys import exit
from sense_hat import SenseHat
from datetime import datetime
from time import sleep
from uuid import getnode
import socket
import csv


def getMac():
    address = getnode()
    h = iter(hex(address)[2:].zfill(12))
    return ":".join(i + next(h) for i in h)

print (getMac())
url = "http://10.160.50.195/humidity.php"
humidityFileLoc = "/home/pi/Desktop/Data/humidity.txt"
sense = SenseHat()


def is_connected():
    try:
        # connect to the host -- tells us if the host is actually
        # reachable
        socket.create_connection(('10.160.50.195', 80))
        return True
    except OSError:
        pass
    return False

while True:
    data = {'humidity': sense.get_humidity(), 
            'date': str(datetime.now().strftime("%Y-%m-%d")), 
            'timestamp': str(datetime.now().strftime("%H:%M:%S")),
            'mac': str(getMac())
            }
    print (is_connected())
    if is_connected() == True:
        print("posting data")
        if(os.path.isfile(humidityFileLoc) == True):
            print ("posting filedata")
            fileData = {}
            with open(humidityFileLoc, "r") as f:
                reader = csv.reader(f)
                for row in reader:
                    key = row[0]
                    fileData[key] = row[1:]
        print (data)
        r = requests.post(url, data)
        print (r)

    else:
        print("error connecting to server, writing to file")
        if(os.path.isfile(humidityFileLoc) == False):
            HumidFile = open(humidityFileLoc, 'w')
            HumidFile.close()
    
        HumidFile = open(humidityFileLoc, "a")
        HumidFile.write(str(data))
        HumidFile.write('\n')
        HumidFile.close()

    sleep(2)
    
