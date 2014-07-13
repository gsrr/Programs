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
		print "In Child Process: PID# %s" % os.getpid()

		sys.stdout.flush()
		try:
			os.execlp("python","ThePythonProgram","pyecho.py")
		except:
			print "Cannot spawn execlp..."
	else:
		print "In Parent Process: PID# %s" % os.getpid()
		print os.read(fd, 100) # in fact, this line prints out the "In Child Process..." sentence above!

		os.write(fd,"message one\n")
		print os.read(fd, 100)        # message one
		time.sleep(2)
		os.write(fd,"message two\n")
		print os.read(fd, 10000)      # pyecho starting...\n MESSAGE ONE
		time.sleep(2)
		print os.read(fd, 10000)      # message two \n MESSAGE TWO

if __name__ == "__main__":
	my_pty_fork()
