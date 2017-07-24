import requests
import os
from sys import exit
from sense_hat import SenseHat
from datetime import datetime
from time import sleep

url = "http://10.160.50.195/humidity.php"
humidityFileLoc = "/var/www/html/humidity.csv"
tempFile = "/var/www/html/temp.csv"
sense = SenseHat()
while (1):
    data = {'humidity': sense.get_humidity(), 
            'date': str(datetime.now().strftime("%Y-%m-%d")), 
            'timestamp': str(datetime.now().strftime("%H:%M:%S"))
            }
    try:
        print("posting data")
        r = requests.post(url, data)
        print r

    except requests.exceptions.ConnectTimeout:
        print("error connecting to server, writing to file")
        if(os.path.isfile(humidityFile) == False):
            with open(humidityFileLoc, "w") as f:
                humidityFile.write(str(data))
            humidityFile.close()
        else:
            with open(humidityFileLoc, "a") as f:
                f.write(str(data))

    except requests.exceptions.InvalidURL:
        print("invadlid url", url)
        print("exitting")
        sys.exit(1)
    except requests.exceptions.HTTPError:
        print("HTTP error, exitting")
        sys.exit(1)
    sleep(10)
