#!/usr/bin/python
# -*- coding: utf-8 -*-

import sys
import time
from socket import *
import pickle
import inspect
import traceback
import datetime
import random
import os
import threading
import select
#### ift class ####
from HADefine import *
from HAObject import *




class HACmdObj():
	def __init__(self, HACmdDict, dataObjList = None):
		self.HACmdDict = HACmdDict
		self.dataObjList = dataObjList
		
class HeartBeatClient(object):
	def __init__(self, remoteIP, port):
		self.remoteIP = remoteIP
		self.port = port
		self.RemoteStatus = 0
		self.__g_reqId = 0
		self.__g_socket = self.__createSocket(remoteIP, port)
		self.count = 0
		
	def __createSocket(self, remoteIP, port):
		while True:
			try:
				serverSocket = socket(AF_INET, SOCK_STREAM)
				serverSocket.settimeout(5)
				serverSocket.connect((remoteIP, port))
				serverSocket.settimeout(None)
				return serverSocket
			except:
				time.sleep(5)
				print traceback.format_exc()


			self.__g_socket = self.__createSocket(self.remoteIP, self.port)
				
	#### public ####
	def closeSocket(self):
		try:
			self.__g_socket.send("<<IFT<<"+("BYE").rjust(26)+">>IFT>>")
			self.__g_socket.shutdown(SHUT_RD)
		except:
			print traceback.format_exc()
			
	#### HA cmd ####
	def updateHeartbeat(self):
		self.__g_socket.send("updateStatus")
				

class HeartBeatServer(object):
	def __init__(self, port):
		self.port = port
		self.__server_socket = self.createServerSocket(port)
		self.t_server = threading.Thread(target=self.__recvThread)
		self.t_server.start()
		self.remote_count = 0
	
	def createServerSocket(self, port):
		sock = socket(AF_INET, SOCK_STREAM)
		sock.bind(("", port))
		sock.listen(10)
		return sock
	
	def __recvThread(self):
		input = [self.__server_socket]
		while True:
			inputready,outputready,exceptready = select.select(input,[],[], 10)
			for s in inputready:
				if s == self.__server_socket:
					client , address = s.accept()
					input.append(client)
				else:
					header = s.recv(512).strip()
					if "updateStatus" in header:
						print "updateStatus"
						begin = time.time()
					elif "remoteStatus" in header:
						end = time.time()
						s.send(str(int(end - begin)))
					else:
						input.remove(s)

if __name__ == "__main__":
	heartBeatServer = HeartBeatServer(5599)
	ha_agent = HeartBeatClient(REMOTE_HA_IP, 5599)
	ha_agent.updateHeartbeat()



