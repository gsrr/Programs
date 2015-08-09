
# -*- coding: utf-8 -*-

#從例子看起來就是:
'''
若該number是Fibonacci number, 就拿前一數扣掉目前的number做為age
若不是的話, 就拿前一數加1做為age.
'''

import time

FibonArr = []

def createFibonArr(n):
    global FibonArr
    base = 10000
    FibonArr.append(10000)
    FibonArr.append(9999)
    FibonArr.append(9997)

    preFibon = 1
    curFibon = 2
    for i in range(3, n):
        #print i
        #time.sleep(1)
        if i == preFibon + curFibon:
            FibonArr.append(FibonArr[i-1] - i)
            preFibon = curFibon
            curFibon = i
        else:
            FibonArr.append(FibonArr[i-1] + 1)

        #print FibonArr

def checkio(opacity):
    global FibonArr
    print FibonArr.index(opacity)
    return FibonArr.index(opacity)
    return 0

#These "asserts" using only for self-checking and not necessary for auto-testing
if __name__ == '__main__':
    createFibonArr(5001)
    assert checkio(10000) == 0, "Newborn"
    assert checkio(9999) == 1, "1 year"
    assert checkio(9997) == 2, "2 years"
    assert checkio(9994) == 3, "3 years"
    assert checkio(9995) == 4, "4 years"
    assert checkio(9990) == 5, "5 years"
