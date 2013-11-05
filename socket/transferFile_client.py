import socket
import sys

HOST = '127.0.0.1'
PORT = 8888

s = socket.socket(socket.AF_INET , socket.SOCK_STREAM)
s.connect((HOST , PORT))
fd = open('socket_test.txt' , 'rb')
s.sendall('/tmp/test_socket_version2')
data = fd.read(1024)
print data
while data:
	print "in while"
	s.sendall(data)
	data = fd.read(1024)

fd.close()
s.close()
