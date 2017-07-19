from time import sleep


def paragraph(sText):
    sWord = "<p>"
    sWord += str(sText) + "</p>"
    return sWord
    

while True:
    HumFile = open("/var/www/html/HummidtyData.txt","r")
    TempFile = open("/var/www/html/TemperatureData.txt","r")
    HummidList = HumFile.readlines()
    TempList = TempFile.readlines() 
    HumFile.close()
    TempFile.close()
    
    sPage = ""
    sPage +="<html> "
    sPage +=" <head> "
    sPage +="<title>"
    sPage += " GateWay 1"
    sPage += "</title>"
    sPage += "<meta http-equiv=\"refresh\" content=\"5\" >"
    sPage += " </head> "
    sPage += "<body>"
    sPage += "<h1>"
    sPage += " Gateway Business Centre, Redruth TR15 3RQ" #1st header
    sPage += "</h1>"
    sPage += paragraph("<a href='https://www.google.com/maps/place/Bluefruit+Software,+Gateway+Business+Centre,+Barncoose+Gateway+Park,+Illogan+Highway,+Redruth+TR15+3RQ,+UK/@50.228803,-5.24783,17z/data=!4m2!3m1!1s0x486b1f5c8ba8f665:0x5d7c3f05d682b4c3'>Location</a>")
    sPage += paragraph("Day: " + str(HummidList[-1][0:10]))
    sPage += paragraph("Time: " + str(HummidList[-1][11:19]))
    sPage += paragraph("Hummidity: " + str(HummidList[-1][20:25]))

    sPage += "</body> </html>"

    file = open("/var/www/html/SensorData.html","w")
    file.write(sPage)

    file.close()

    sleep(3)
