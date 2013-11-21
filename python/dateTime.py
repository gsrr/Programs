import time
import datetime


def getTimeDelta(t1 , t2):
	return t1 - t2

def getDurationBySecond(diff):
	return diff.days * 24 * 60 * 60

t1 = "2037-02-20"
t2 = "2036-02-20"
t1 = datetime.datetime.strptime(t1,'%Y-%m-%d')
t2 = datetime.datetime.strptime(t2,'%Y-%m-%d')
print "year , month , day of t1:" , t1.year, t1.month, t1.day
print "year , month , day of t2:" , t2.year, t2.month, t2.day

diff = getTimeDelta(t1,t2)
print "duration by seconds:" , getDurationBySecond(diff)
























