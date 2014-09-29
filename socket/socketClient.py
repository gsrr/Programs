# Echo client program
import socket
import sys


HOST = '172.27.113.11'
PORT = 5100

cmdList={
	"GetRemotePoolSize" : "810 1",
	"GetRemotePool" : "810 0"
}

def sendCommand(cmd):
	s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
	s.connect((HOST, PORT))
	s.sendall(cmd)
	data = s.recv(1024)
	s.close()
	return data


if __name__ == "__main__":
	cmd = cmdList[sys.argv[1]]
	print sendCommand(cmd)
	
