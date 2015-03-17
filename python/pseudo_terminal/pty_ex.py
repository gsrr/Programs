#!/usr/bin/env python
# pyecho.py


import sys
import os
import time
import pty
import fcntl
import time

def isExist(pid):
    try:
        os.kill(pid, 0)
    except OSError:
        return False
    return True


def read_data(fd):
    cnt = 0
    while cnt < 3:
        try:
            data = os.read(fd,1024)
            print data.strip()
        except OSError as e:
            cnt += 1
            if e.errno == 5 or cnt == 3:
                pass
                #sys.exit(0)

        finally:
            time.sleep(1)


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
			#os.execlp("/bin/ls","/bin/ls","-l")
		except:
			print "Cannot spawn execlp..."
	else:
                fl = fcntl.fcntl(fd, fcntl.F_GETFL)
                fcntl.fcntl(fd, fcntl.F_SETFL, fl | os.O_NONBLOCK)
		print "In Parent Process: PID# %s" % os.getpid()
                read_data(fd)
                
                while isExist(child_pid):
                    msg = sys.stdin.readline()
                    os.write(fd, msg)
                    read_data(fd)
                    #data = os.read(fd,1024)
                    #print data.strip()

if __name__ == "__main__":
	my_pty_fork()
