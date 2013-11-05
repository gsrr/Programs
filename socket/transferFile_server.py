import socket
import sys

HOST = '127.0.0.1'
PORT = 8888

s = socket.socket(socket.AF_INET , socket.SOCK_STREAM)

try:
	s.bind((HOST , PORT))
except socket.error , msg:
	sys.exit()

s.listen(10)

conn,addr = s.accept()
print addr
path = conn.recv(1024)
print path
fd = open(path , 'wb')
data = conn.recv(1024)
while data:
	fd.write(data)
	data = conn.recv(1024)

fd.close()
s.close()	
