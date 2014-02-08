import random

def generateNumbers(num , power):
        base = pow(10 , power)
        numbers = []
        for i in range(num):
                number =  int(random.random() * base)
                numbers.append(number)
        return numbers
