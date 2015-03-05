import os
import time

def child():
	while True:
		print "In child process"	
		time.sleep(1)

child_id = os.fork()
if child_id == 0:
	print "This is child:" + str(child_id)
	# if grand-parent is commands.getouput , we should close the file descriptor because it uses os.popen()
	os.close(1)
	os.close(2)
	child()
else:
	print "This is parent:" + str(child_id)
	#os.waitpid(child_id,0)
