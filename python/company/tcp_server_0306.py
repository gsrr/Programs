import socket
import sys
import pycksum
import traceback

LIMIT = 128 * 1000 #128KB

def get_file(paraList):
	global LIMIT
	clientSocket = paraList['clientSocket']
	offset = paraList['offset']
	with open('/root/Noname.jpg', 'rb') as fr:
		fr.seek(offset)
		buffer = fr.read(LIMIT)
		cksum = pycksum.pycksum(buffer).split()[1]
		clientSocket.send(cksum)
		clientSocket.send(buffer)



def createSocket(ip_port):
	s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
	s.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
	s.bind(ip_port)
	s.listen(5)
	return s


class SOCK_ParaOperation:
	def __init__(self, conn, data):
		self.conn = conn
		data_list = data.strip().split("::")
		self.op = data_list[0]
		self.paras = data_list[1:]
		self.paraList = {}
		getattr(self, "paras_" + self.op)()
		
	def paras_GET_FILE(self):
		try:
			paraList = self.paraList
			paraList['clientSocket'] = self.conn
			paraList['path'] = self.paras[0]
			paraList['offset'] = int(self.paras[1])
		except:
			print traceback.format_exc()

if __name__ == "__main__":
	IP = 'localhost'
	PORT = 9000
	OP_BUFFER = 1024 
	s = createSocket((IP, PORT))

	while True:
		conn, addr = s.accept()
		print "Accept:" , addr
		
		data = conn.recv(OP_BUFFER)
		sock_paras = SOCK_ParaOperation(conn, data) #parse command
		func = getattr(sys.modules[__name__], sock_paras.op.lower()) #call command function
		func(sock_paras.paraList)
		
		conn.close()
		print "Close:", addr


