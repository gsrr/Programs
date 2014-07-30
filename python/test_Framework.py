import sys


def test_item_4(paras):
        print "test_item_4"
        print paras['op']
        return {'status' : 4}

def test_item_3(paras):
	print "test_item_3"
	print paras['op']
        return {'status' : 3}

def test_item_2(paras):
	print "test_item_2"
	print paras['op']
        return {'status' : 2}

def test_item_1(paras):
	print "test_item_1"
	print paras['op']
        return {'status' : 1}


testList = {
        'addRR' : [
		{'name' : 'test_item_1'} , 
		{'name' : 'test_item_2'} , 
		{'name' : 'test_item_3'}  
	],
        'editRR':[
                {'name' : 'test_item_1'}, 
                {'name' : "test_item_4"},
                {'name' : "test_item_2"}
        ]
}

def doTest(func):
        def wrap_func(paras):
                testItems = testList[paras['op']]
                for item in testItems:
                        testFunc = getattr(sys.modules[__name__] , item['name'])
                        ret = testFunc(paras)
                        if ret['status'] != 0 and paras['debug'] == 'False':
                                return ret
                func(paras)
        return wrap_func



@doTest
def editRR(paras):
        print 'do edit RR'

@doTest
def addRR(paras):
        print 'do add RR'


if __name__ == "__main__":
        paras = {
                'op' : sys.argv[1],
                'para' : 'paras',
                'debug' : sys.argv[2]
        }
	getattr(sys.modules[__name__] ,paras['op'])(paras)
