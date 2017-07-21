#!/usr/bin/python           # This is client.py file

import socket               # Import socket module

s = socket.socket()         # Create a socket object
ip_addr = raw_input('What IP ?: ')
message = raw_input('Message to send: ')

port = 1776                # Reserve a port for your service.

s.connect((ip_addr, port))
print s.recv(1024)
s.send(message)
s.close                     # Close the socket when done


