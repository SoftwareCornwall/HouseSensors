from sense_hat import SenseHat
from time import sleep
from datetime import datetime
import os



sense = SenseHat()

HummidLocation = "/var/www/html/HummidtyData.txt"
TemperatureLocation = "/var/www/html/TemperatureData.txt"

sMessageHummid = ""
sMessageTemp = ""

if os.path.isfile(HummidLocation) == False:
    Hummidfile = open(HummidLocation,"w")
    Hummidfile.close()

if os.path.isfile(TemperatureLocation) == False:
    Temperaturefile = open(TemperatureLocation,"w")
    Temperaturefile.close()

while True:
    
    Hummidfile = open(HummidLocation,"a")
    Temperaturefile = open(TemperatureLocation,"a")
    


    sMessageHummid = "\n"
    sMessageTemp ="\n"

    
    #Hummidity
    humidity = sense.get_humidity()
    sMessageHummid += str(datetime.now().strftime("%Y-%m-%d %H:%M:%S"))
    sMessageHummid += " "
    sMessageHummid += str(round(sense.humidity, 2))

    
    
    #Temperature
    temp = sense.get_temperature()
    sMessageTemp += str(datetime.now().strftime("%Y-%m-%d %H:%M:%S"))
    sMessageTemp += " "        
    sMessageTemp += str(round(sense.temperature, 2))

    Hummidfile.write(sMessageHummid)
    Temperaturefile.write(sMessageTemp)
    
    print (sMessageHummid)
    print (sMessageTemp)
    
    Hummidfile.close()
    Temperaturefile.close()
    
    sleep(3) #Time in seconds between each reading
    
 
