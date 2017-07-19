from time import sleep

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
    sPage += "<meta http-equiv=\"refresh\" content=\"5\" >"
    sPage += " </head> "
    sPage += "<body> <p> "
    sPage += "Day: " + str(HummidList[-1][0:9])
    sPage += "</p> </body> </html>"

    file = open("netv2.html","w")
    file.write(sPage)

    file.close()

    sleep(3)
