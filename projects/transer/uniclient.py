import socket
import sys
import time
import struct
import binascii
import os

class Client:
	def __init__(self, host, port):
		self.s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
		self.s.connect((host, port))
		
	
	def test(self, args):
		sock = self.s
		while True:
			time.sleep(1)
		#sock.close()

	def send_file_conf(self, args):
		sock = self.s
		size = os.path.getsize("/tmp/systemSetting.bin")
		sock.send("SEND_FILE::CONF::%d::                   "%(size))
		ret = sock.recv(128)
		if int(ret) != 0:
			return

		with open("/tmp/systemSetting.bin", "rb") as fr:
			data = fr.read(128)
			sendSize = 0
			while data and sendSize < size:
				crc32 = format(binascii.crc32(data) & 0xFFFFFFFF, 'x').upper()
				length = int(len(data))
				meta = "%s::%s::"%(crc32, length)
				print meta
				sock.send(meta)
				ret = sock.recv(128)
				sock.send(data)
				ret = sock.recv(128)
				print ret
				if int(ret) != 0:
					fr.seek(-1 * length , 1)
				else:
					sendSize = sendSize + len(data)
				data = fr.read(128)
				
			meta = "%s::%s::"%(0, 0)
			print meta
			sock.send(meta)
			print "send finish"
		sock.close	

	def create_slog(self, args):
		sock = self.s
		sock.send("CREATE::SLOG::")
		data = sock.recv(1024)
		print data
		sock.close()

	def create_conf(self, args):
		sock = self.s
		sock.send("CREATE::CONF::")
		data = sock.recv(1024)
		print data
		sock.close()

	def create_timeout(self, args):
		sock = self.s
		sock.send("CREATE::TESTTIMEOUT::")
		data = sock.recv(1024)
		print data
		sock.close()

	def create_diag(self, args):
		print 'create_config_data'
		sock = self.s
		sock.send("CREATE::DIAG")
		data = sock.recv(1024)
		print data
		sock.close()
	
	def get_crc(self, args):
		sock = self.s
		sock.send("GET_CRC::CONF::0::20000")
		data = sock.recv(1024)	
		data = struct.unpack("2I", data)
		print struct.pack("2I", int(data[0]), int(data[1]))
		print data
	
	def get_file(self, args):
		sock = self.s
		size = 0
		with open('logTest', 'wb') as fw:
			while size < 73595:
				print size
				sock.send("GET_FILE::SLOG::%s::5000"%size)
				size = size + 5000
				data = sock.recv(5000)	
				fw.write(data)
		
		print "finish"

		
	def config_fin(self, args):
		sock = self.s
		sock.send("CONFIG_FIN")
		data = sock.recv(1024)	
		print data

	def dispatch(self, paras):
		print paras
		func = getattr(self, paras[1])
		ret = func(paras)
		return ret

def main():
	port = int(sys.argv[1])
	cli = Client('localhost', port)	
	while True:
		msg = sys.stdin.readline()
		msg = msg.strip()
		cmd = ['test', msg]
		cli.dispatch(cmd)
		if msg == 'config_fin':
			sys.exit(0)

if __name__ == "__main__":
	main()


