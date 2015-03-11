#!/usr/bin/env python
# pyecho.py

import sys
import os

print "pyecho starting..."

while True:
    #os.system("stty -echo")
    data = sys.stdin.readline().upper()
    #os.system("stty echo")
    print data.strip()
    '''
    _stdout = sys.stdout
    null = open(os.devnull,'wb')
    sys.stdout = sys.stderr = null
    data = sys.stdin.read().upper()
    '''
