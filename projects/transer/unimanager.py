import subprocess
import random
import traceback
import os
import time


def cleanGarbage():
	cmd = "ps -ef | grep uniserver | awk '{print $2}' | xargs kill -9"
	os.system(cmd)

def main():
	cleanGarbage()
	ret = 0
	retry = 0
	port = 0
	while retry < 3:
		port = random.randint(9900, 10000)
		pid = None
		cmd = "/bin/python /var/apache/tomcat/webapps/NAS/misc/agent/python/uni/uniserver.py %d"%port
		try:
			proc = subprocess.Popen(cmd , shell = True, stdout=subprocess.PIPE)
			line = proc.stdout.readline().strip()
			proc.stdout.close()
			if "Server start!!" in line: 
				ret = 0
				pid = proc.pid
				break
			elif "Address in use" in line:
				ret = 125
			else:
				ret = -1
		except:
			print traceback.format_exc()
			ret = -1 
		retry += 1

	if ret == 0:
		print "Server_Start::" + str(pid) + "::" + str(port)
	else:
		if ret == 125:
			print "Address in use"
		else:
			print "Start_Fail"

if __name__ == "__main__":
	main()
