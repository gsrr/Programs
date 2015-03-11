#!/usr/bin/env python
# pyecho.py


import sys
import os
import time
import pty

def my_pty_fork():
	try:
		( child_pid, fd ) = pty.fork()    # OK
	except OSError as e:
		print str(e)

	if child_pid == 0:
		sys.stdout.flush()
                os.system("stty -echo")
		try:
			os.execlp("python","ThePythonProgram","pyecho.py")
		except:
			print "Cannot spawn execlp..."
	else:
		print "In Parent Process: PID# %s" % os.getpid()
                data = os.read(fd,1024)
                print data.strip()

                while True:
                    msg = sys.stdin.readline()
                    os.write(fd, msg)
                    data = os.read(fd,1024)
                    print data.strip()

if __name__ == "__main__":
	my_pty_fork()
