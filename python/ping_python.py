import os
import socket


def main():
	for i in range(1,256):
		ip = "192.168.1.%d"%(i)
		cmd = "ping %s -c 1 1>/dev/null 2>1"%(ip)
		ret = os.system(cmd);
		if ret == 0:
			print ip
			print socket.gethostbyaddr(ip)


if __name__ == "__main__":
	main()
