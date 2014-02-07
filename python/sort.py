import random
import sys


def getDigits(numbers , base):
        digits = []
        for i in range(len(numbers)):
                digits.append(numbers[i]//base % 10)
        return digits


def getEndLoop(num):
        endLoop = []
        for i in range(num):
                endLoop.append(0)
        return endLoop

def radix(numbers):
        bucket = []
        for i in range(10):
                bucket.append([])
        base = 1
        endLoop = getEndLoop(len(numbers))

        while True:
                digits = getDigits(numbers , base)
                base = base * 10
                if digits == endLoop:
                        break;
                for i in range(len(digits)):
                        bucket[digits.pop()].append(numbers.pop())

                for i in range(10):
                        for j in range(len(bucket[i])):
                                numbers.append(bucket[i].pop())

                
        
def generateNumbers(num):
        numbers = []
        for i in range(num):
                number =  int(random.random() * 1000)
                numbers.append(number)
        return numbers

if __name__ == "__main__":
        numbers = generateNumbers(10)
        func = getattr(sys.modules[__name__] , sys.argv[1])
        print "Before:" , numbers
        func(numbers)
        print "After:" , numbers
