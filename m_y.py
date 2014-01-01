#first example
class Base_1(object):
	def first(self):
		print "Base:First"
	def second(self):
		print "Base:second"

class Derived_1(Base_1):
	def first(self):
		print "Derived:First"


def firstExampleTest():
	obj = Derived_1()
	obj.first()
	obj.second()


#second example
class Base_2(object):
	def first(self):
		print "Base_2:First"
	def second(self):
		raise NotImplementedError

class Sub_2(Base_2):
	def first(self):
		print "Sub_2: First"

def secondExTest():
	obj = Sub_2()
	obj.first()
	obj.second()

if __name__ == "__main__":
	import traceback
	firstExampleTest()
	try:
		secondExTest()
	except:
		print traceback.format_exc()


