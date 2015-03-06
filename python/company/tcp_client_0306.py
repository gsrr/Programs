import socket

IP = 'localhost'
PORT = 9000

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.connect((IP, PORT))
s.send("GET_FILE::test::129")
with open("test.jpg", "wb") as fw:
	data = s.recv(1024)
	while data:
		fw.write(data)
		data = s.recv(1024)

s.close()
