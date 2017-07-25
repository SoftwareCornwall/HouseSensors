#!/usr/bin/python           # This is server.py file

import socket      # Import socket module
import os
import datetime

now = datetime.datetime.now()
HouseNumber = 21

WaterDataLocation = "/home/pi/Desktop/HouseSensors/toxicCheese/House" + str(HouseNumber) + "/"+ str(HouseNumber) +"WaterData_" + (now.strftime("%Y_%m_%d")) + ".csv"

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)         # Create a socket object
s.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
host = socket.gethostname() # Get local machine name
port = 1776                # Reserve a port for your service.

s.bind(('', port))        # Bind to the port

s.listen(5)                 # Now wait for client connection.
while True:

       c, addr = s.accept()     # Establish connection with client.
       print ('Got connection from', addr)
       WaterFile = open(WaterDataLocation, "r")
       WaterData = WaterFile.readlines()
       Message = str(WaterData[-1])
       WaterFile.close()
       c.send(Message)
       c.close()                # Close the connection
       

