import requests
import os
from sys import exit
from sense_hat import SenseHat
from datetime import datetime
from time import sleep
from uuid import getnode

def getMac():
    address = getnode()
    h = iter(hex(address)[2:].zfill(12))
    return ":".join(i + next(h) for i in h)

print (getMac())
url = "http://10.160.50.195/humidity.php"
humidityFileLoc = "/var/www/html/humidity.csv"
tempFile = "/var/www/html/temp.csv"
sense = SenseHat()
while (1):
    data = {'humidity': sense.get_humidity(), 
            'temperature': sense.get_temperature(),
            'date': str(datetime.now().strftime("%Y-%m-%d")), 
            'timestamp': str(datetime.now().strftime("%H:%M:%S")),
            'mac': str(getMac())
            }
    try:
        print("posting data")
        if(os.path.isfile(humidityFileLoc) == True):
            print ("posting filedata")
            with open(humidityFileLoc, "r") as f:
                reader = csv.reader(f)
                fileData = {}
                for row in reader:
                    key = row[0]
                    fileData[key] = row[1:]
                    tr = requests.post(url, fileData)
            os.remove(humidityFileLoc)
            print ("removed: ", humidityFileLoc)
        r = requests.post(url, data)
        print r

    except requests.exceptions.ConnectTimeout:
        print("error connecting to server, writing to file")
        if(os.path.isfile(humidityFileLoc) == False):
            with open(humidityFileLoc, "w") as f:
                writer = csv.writer(f)
                for key, value in data:
                    writer.writerow([key, value])
        else:
            with open(humidityFileLoc, "a") as f:
                writer = csv.writer(f)
                for key, value in data:
                    writer.writerow([key, value])
    except requests.exceptions.InvalidURL:
        print("invadlid url", url)
        print("exitting")
        sys.exit(1)
    except requests.exceptions.HTTPError:
        print("HTTP error, exitting")
        sys.exit(1)
    except KeyboardInterrupt:
        print("exitting")
        sys.exit(1)
    sleep(10)
    
