import socket
import sys
import traceback
import commands
import threading
import time
import os
import struct
import binascii
import signal

BUFFER = 1024
TIMEOUT = 6000

class Singleton(object):
	_instance = None
	def __new__(self):
		if not isinstance(self._instance, self):
			self._instance = object.__new__(self)
		return self._instance

class LogServer(Singleton):
	_fd = None
	def createFD(self):
		if self._fd == None:
			self._fd = open('/var/log/uniserver.log', 'a')
		return self._fd

	def log(self,logStr):
		t = time.ctime(time.time())
		self._fd.write("[%s] %s"%(t, logStr))

	def close(self):
		print "close fd"
		self._fd.close()

def log(logStr):
	ls.log(logStr)

def signal_handler(signal, frame):
	print signal
	print('You pressed Ctrl+C!')
	sys.exit(0)


def saveDataToFile(data):
	print len(data)
	with open("/tmp/test", "w") as fw:
		fw.write(data)

def send_file_conf(paraList):
	log("send_file_conf:%s"%(str(paraList)))
	
	clientSocket = paraList['clientSocket']
	size = paraList['size']
	if size > 0:
		clientSocket.send("0")
	else:
		clientSocket.send("1")
		return

	data = ''
	#while len(data) < size:
	while True:
		item = clientSocket.recv(BUFFER)
		items = item.split("::")
		print items
		crc32_get = int(items[0], 16)
		length = int(items[1])
		if crc32_get > 0 and length > 0:
			clientSocket.send("0")
			tmpData = clientSocket.recv(length)
			#saveDataToFile(tmpData)
			crc32 = binascii.crc32(tmpData) & 0xFFFFFFFF
			print crc32, crc32_get
			if crc32 == crc32_get:
				clientSocket.send("0")###
				print "send 0"
				data = data + tmpData
			else:
				clientSocket.send("1")
				print "send 1"
		else: #close --> crc32_get = 0 and length == 0
			clientSocket.send("0")
			print "finish"
			break

	
	with open("/tmp/restoreSetting", "wb") as fw:
		fw.write(data)
	
	clientSocket.close()

def send_file(paraList):
	func = getattr(sys.modules[__name__], "send_file_" + paraList['op'])
	func(paraList)


def start_to_systemBackup(paraList):
	clientSocket = paraList['clientSocket']
	cmd = paraList['cmd']
	dest = paraList['dest']
	output = commands.getoutput(cmd).strip()
	output = output.split("\"")
	filePath = output[2] + output[0]
	cmd = "mv %s %s"%(filePath, dest)
	os.system(cmd)
	size = os.path.getsize(dest)	
	size = struct.pack("i",int(size))
	clientSocket.send(str(size))

def create_testtimeout(paraList):
	print "create test"
	global TIMEOUT
	os.system("rm -rf /tmp/systemSetting.bin")
	paraList['cmd'] = "python /var/apache/tomcat/webapps/NAS/misc/maintenance/SystemBackup.py 0"		
	paraList['dest'] = '/tmp/systemSetting.bin'
	time.sleep(TIMEOUT)
	start_to_systemBackup(paraList)

def create_conf(paraList):
	print "create conf"
	os.system("rm -rf /tmp/systemSetting.bin")
	paraList['cmd'] = "python /var/apache/tomcat/webapps/NAS/misc/maintenance/SystemBackup.py 0"		
	paraList['dest'] = '/tmp/systemSetting.bin'
	start_to_systemBackup(paraList)
	
def create_slog(paraList):
	print 'create_log_file'
	os.system("rm -rf /tmp/systemLog.bin")
	paraList['cmd'] = "python /var/apache/tomcat/webapps/NAS/misc/maintenance/SystemBackup.py 1"		
	paraList['dest'] = '/tmp/systemLog.bin'	
	start_to_systemBackup(paraList)
	
def create_diag(paraList):
	print 'create_config_diag'
	clientSocket = paraList['clientSocket']
	cmd = "python /var/apache/tomcat/webapps/NAS/misc/HAAgent/ExportWeb/System/getDiagnosticReport.py"		
	output = commands.getoutput(cmd).strip()
	ret = eval(output)
	print ret
	size = None
	if ret['status'] == 0:
		data = ret['data']
		oldPath = data['path'] + data['name']
		newPath = data['path'] + "DiagnosticReport_last"
		os.rename(oldPath, newPath)
		size = os.path.getsize(newPath)	
		size = struct.pack("i",int(size))
		clientSocket.send(str(size))
	else:
		clientSocket.send("-1")

	
#CONF, SLOG, DIAG, TEST
def create(paraList):
	try:
		op = 'create_' + paraList['op']  
		print len(op)
		func = getattr(sys.modules[__name__], op.strip())
		func(paraList)
	except:
		print traceback.format_exc()
		raise	


def get_crc(paraList):
	print "get_crc:", paraList
	clientSocket = paraList['clientSocket']
	path = paraList['path']
	offset = paraList['offset']
	size = paraList['size']
	with open(path, 'rb') as fr:
		fr.seek(offset)
		buffer = fr.read(size)
		cksum = binascii.crc32(buffer) & 0xFFFFFFFF
		data = struct.pack("2I",int(cksum),int(len(buffer)))
		print data
		clientSocket.send(data)

def get_file(paraList):
	clientSocket = paraList['clientSocket']
	path = paraList['path']
	offset = paraList['offset']
	size = paraList['size']
	with open(path, 'rb') as fr:
		fr.seek(offset)
		buffer = fr.read(size)
		clientSocket.send(buffer)

def config_fin(paraList):
	clientSocket = paraList['clientSocket']
	clientSocket.close()

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
		if len(data_list) > 1:
			self.paras = data_list[1:]
		self.paraList = {}
		print "paras_" + self.op
		getattr(self, "paras_" + self.op)()
	

	def paras_SEND_FILE(self):
		try:
			paraList = self.paraList
			paraList['clientSocket'] = self.conn
			paraList['op'] = self.paras[0].lower()
			paraList['size'] = int(self.paras[1])
		except:
			print traceback.format_exc()
		
	def paras_CREATE(self):
		try:
			paraList = self.paraList
			paraList['clientSocket'] = self.conn
			paraList['op'] = self.paras[0].strip().lower()
		except:
			print traceback.format_exc()
		

	def paras_GET_CRC(self):
		self.paras_GET_FILE()

	def paras_GET_FILE(self):
		path = {
			'CONF' : '/tmp/systemSetting.bin',
			'SLOG' : '/tmp/systemLog.bin',
			'DIAG' : '/nastmp/DiagnosticReport_last',
			'TESTTIMEOUT' : '/tmp/systemLog.bin'
		}
		try:
			paraList = self.paraList
			paraList['clientSocket'] = self.conn
			paraList['path'] = path[self.paras[0]]
			paraList['offset'] = int(self.paras[1])
			paraList['size'] = int(self.paras[2])
		except:
			print traceback.format_exc()

	def paras_CONFIG_FIN(self):
		try:
			paraList = self.paraList
			paraList['clientSocket'] = self.conn
		except:
			print traceback.format_exc()

def clientHandler(conn):
	OP_BUFFER = 1024 
	while True:
		try:
			data = conn.recv(OP_BUFFER)
			print data
			if len(data) == 0:
				break
			sock_paras = SOCK_ParaOperation(conn, data) #parse command
			func = getattr(sys.modules[__name__], sock_paras.op.lower()) #call command function
			func(sock_paras.paraList)
		except socket.error as e:
			print traceback.format_exc()
			if e.errno == 9:
				print "fd error , it has been closed"
				break
		
			print traceback.format_exc()
			conn.close()
			print "Close:", addr
			break
		time.sleep(1)	
	conn.close()
	print "Close:", addr
	
		

if __name__ == "__main__":
	ls = LogServer()
	ls.createFD()
	IP = ''
	PORT = int(sys.argv[1])
	try:
		s = createSocket((IP, PORT))
		print "Server start!!"
		sys.stdout.flush()
		conn, addr = s.accept()
		conn.settimeout(60)
		conn.setblocking(1)
		print "Accept:" , addr
		t = threading.Thread(target=clientHandler, args = (conn,))
		time.sleep(1)
		t.start()
	except socket.error, err:
		print "Address in use:" + str(err.errno)
	finally:
		t.join(600)
		ls.close()
		sys.exit(0)
		


