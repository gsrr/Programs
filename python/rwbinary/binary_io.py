# -*- coding: utf-8 -*-



fo = open("foo.txt", "wb")
string='這是字串\naaaa'


for i in range(0,len(string)):
        print ord(string[i])
# Close opend file
fo.write(string)
fo.close()


with open("foo" , "wb") as f:
        for counter in xrange(100):
                print counter
                f.write(chr(counter))
                f.write(chr(int("00100001" , 2)))
                
