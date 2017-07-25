import requests
import os
from sys import exit
from sense_hat import SenseHat
from datetime import datetime
from time import sleep
from uuid import getnode
import csv

def getMac():
    address = getnode()
    h = iter(hex(address)[2:].zfill(12))
    return ":".join(i + next(h) for i in h)

url = "http://10.160.50.195/humidity.php"
humidityFileLoc = "/home/pi/Desktop/humidity.csv"
tempFile = "/home/pi/Desktop/temp.csv"
sense = SenseHat()

while (1):
    data = {'humidity': sense.get_humidity(), 
            'temperature': sense.get_temperature(),
            'date': str(datetime.now().strftime("%Y-%m-%d")), 
            'timestamp': str(datetime.now().strftime("%H:%M:%S")),
            'mac': str(getMac())
            }
    try:
        if(os.path.isfile(humidityFileLoc) == True):
            with open(humidityFileLoc, "r") as f:
                reader = csv.reader(f)
                fileData = {}
                for row in reader:
                    key = row[0]
                    fileData[key] = row[1:]
                    tr = requests.post(url, fileData)
            os.remove(humidityFileLoc)
        r = requests.post(url, data)
        print r

    except requests.exceptions.ConnectionError:
        print("error connecting to server, writing to file")
        if(os.path.isfile(humidityFileLoc) == False):
            with open(humidityFileLoc, "w") as f:
                writer = csv.DictWriter(f, data.keys())
                writer.writerow(data)
        else:
            with open(humidityFileLoc, "a") as f:
                writer = csv.DictWriter(f, data.keys()) 
                writer.writerow(data)
    except requests.exceptions.InvalidURL:
        print("invadlid url", url)
        print("exitting")
        sys.exit(1)
    except KeyboardInterrupt:
        print("exitting")
        sys.exit(1)
    sleep(10)
    
