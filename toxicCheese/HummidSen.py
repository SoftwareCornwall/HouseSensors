from sense_hat import SenseHat
from time import sleep
from datetime import datetime



sense = SenseHat()
Time = ""
sMessage = ""
file = open("HumTemp.txt","w")
file.close()

while True:
    
    file = open("HumTemp.txt","a")
    humidity = sense.get_humidity()
    temp = sense.get_temperature()

    sMessage = "\n"
    sMessage += "TimeStamp: "
    sMessage += str(datetime.now().strftime("%Y-%m-%d %H:%M:%S"))
    sMessage += "   Humidity: "
    sMessage += str(round(sense.humidity, 2))
    sMessage += "   Temp: "
    sMessage += str(round(sense.temperature, 2))

    file.write(sMessage)
    print (sMessage)
    file.close()
    
    sleep(3)
    
 
