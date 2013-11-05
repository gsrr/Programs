 #!/usr/bin/python
# -*- coding: ascii -*-

import sys
import os
import pexpect
import time

def uploadFileToGit(fileName , message , password):
	
	os.system("git add %s"%(fileName))
	os.system("git add README.md")
	time.sleep(2)
	os.system("git commit -m %s"%(message))
	time.sleep(2)
	child = pexpect.spawn("git push")
	print child.expect("Username")
	print child.sendline("gsrr")
	print child.expect("Password")
	print child.sendline(password)
	print child.expect("Total")




if __name__ == "__main__":
	if len(sys.argv) < 4:
		print "three parameter: file name , message , password"
	else:
		uploadFileToGit(sys.argv[1] , sys.argv[2] , sys.argv[3])
