import os
import time
import sys

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
        print "bbb"
        obj = Sub_2()
        obj.first()
        obj.second()

#decorator in python(function)
def dec(func):
        a = 1
        b = a + 1
        c = b + func()
        return c

#hello=dec( hello() )
@dec
def hello():
        return 5

def thirdExTest():
        print hello

#decorator in python(class)
class dec_class(object):
        def __init__(self , func):
                self.func = func

        def __call__(self):  #called when the instance is called as a function.
                a = 2
                b = a + 2
                c = b + self.func()
                return c

#hello_class = dec_class(hello_class)
@dec_class
def hello_class():
        return 6

def fourExTest():
        print hello_class()
     

#decorator pattern
class foo(object):
        def f1(self):
                print "f1"
        def f2(self):
                print "f2"

class decorator_foo(object):
        def __init__(self , decoratee):
                self.decoratee = decoratee
        def f1(self):
                print "decorator f1"
                self.decoratee.f1()
        def __getattr__(self , name): #Called when an attribute lookup has not found the attribute in the usual places.
                return getattr(self.decoratee , name)

def fiveExTest():
        u = foo()
        v = decorator_foo(u)
        v.f1()
        v.f2()

def dec_six_hello(f):
        def wrapper(a , b):
                a = a + 1
                b = b + 1
                c = f(a , b)
                return c + 1
        return wrapper                

#six_hello = dec_six_hello(six_hello)
@dec_six_hello
def six_hello(a , b):
        return a + b;
def sixExTest():
        print six_hello(1 , 3)
        
def child():
        print "child:" , os.getpid()

def sevenTest():
      newpid = os.fork()
      if newpid == 0:
              child()
              sys.exit()
      else:
              print "parent:" , os.getpid() , newpid

def eightTest():
        print "sleeping..."
        time.sleep(3)
        print "sleep after 3 seconds!!"

if __name__ == "__main__":
        import traceback
        firstExampleTest()
        try:
                secondExTest()
        except:
                print traceback.format_exc()
        
        print "Third: decorator in python (function)"
        thirdExTest()

        print "Four: decorator in python (class)"
        fourExTest()

        print "Five: decorator pattern" 
        fiveExTest()

        print "Six: decorator in python (add parameter)"
        sixExTest()

        print "Seven: fork test"
        sevenTest()
        
        print "Eight: sleep test"
        eightTest()

























