import sys


def test_item_4(object):
	print "test_item_4"
	print object['op']

def test_item_3(object):
	print "test_item_3"
	print object['op']

def test_item_2(object):
	print "test_item_2"
	print object['op']

def test_item_1(object):
	print "test_item_1"
	print object['op']



def doTest(testList):
	for item in testList:
		testFunc = getattr(sys.modules[__name__] , item['name'])
		testFunc(item['para'])

def editRR():
	RRObject = {'op' : 'editRR'}
	testList = [
		{'name' : 'test_item_1' , 'para' : RRObject} , 
		{'name' : "test_item_4" , 'para' : RRObject} ,
		{'name' : "test_item_2" , 'para' : RRObject}
	]
	doTest(testList)

def addRR():
	RRObject = {'op' : 'addRR'}
	testList = [
		{'name' : 'test_item_1' , 'para' : RRObject} , 
		{'name' : "test_item_2" , 'para' : RRObject} ,
		{'name' : "test_item_3" , 'para' : RRObject}
	]
	ret = doTest(testList)




if __name__ == "__main__":
	operation = sys.argv[1]
	func = getattr(sys.modules[__name__] , operation)
	func()
