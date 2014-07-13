# -*- coding: utf-8 -*-
import pexpect
import os
import unittest




try:
	os.system('rm -rf the_first.test')
	child = pexpect.spawn('python test.py')
	#child = pexpect.spawn(123)
	child.expect('name:')
	child.sendline('the_first')
except:
	raise



#if __name__ == '__main__':
	
