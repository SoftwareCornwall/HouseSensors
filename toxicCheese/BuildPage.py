from time import sleep

while True:
    HumTemp = open("/var/www/html/HumTemp.txt","r")
    lineList = HumTemp.readlines()
    HumTemp.close()

    sPage = ""
    sPage +="<html> "
    sPage +=" <head> "
    sPage += " </head> "
    sPage += "<body> <p> "
    sPage += str(lineList[-1])
    sPage += "</p> </body> </html>"

    file = open("net.html","w")
    file.write(sPage)

    file.close()

    sleep(3)
