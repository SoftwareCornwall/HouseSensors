#!/usr/bin/python           # This is server.py file

import socket               # Import socket module

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)         # Create a socket object
s.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
host = socket.gethostname() # Get local machine name
port = 1776                # Reserve a port for your service.

s.bind(('', port))        # Bind to the port

s.listen(5)                 # Now wait for client connection.
while True:
       c, addr = s.accept()     # Establish connection with client.
       print 'Got connection from', addr
       c.send('Thank you for connecting')
       c.close()                # Close the connection

