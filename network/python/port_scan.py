
import socket import * 
import sys

if __name__ == '__main__':
        if len(sys.argv) == 0:
                print 'Enter target ip'
                sys.exit(0)
        target = sys.argv[1]
        targetIP = gethostbyname(target)
        print 'Starting scan on host ', targetIP
        #scan reserved ports
        for i in range(20, 1025):
                s = socket(AF_INET, SOCK_STREAM)
                result = s.connect_ex((targetIP, i))
                if(result == 0) :
                        print 'Port %d: OPEN' % (i,)
        s.close()
