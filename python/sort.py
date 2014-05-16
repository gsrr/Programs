import sys
import lib_number


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
                              


def insert(numbers, index):
        for i in range(index, 0, -1):
                if numbers[i] < numbers[i-1]:
                        numbers[i] , numbers[i-1] = numbers[i-1] , numbers[i]
 
                

def insertion_sort(numbers):
        for i in range(0 , len(numbers)):
                insert(numbers, i)


def createBucket():
        bucket = []
        for i in range(10):
                bucket.append([])

        return bucket


def putNumberIntoBucket(numbers , digit , bucket):
        base = pow(10 , digit)
        for i in range(len(numbers)):
                num = numbers.pop()
                dig = (num / base) % 10
                bucket[dig].append(num)


def takeNumberFromBucket(numbers , bucket):
        for i in range(10):
                while len(bucket[i]) != 0:
                        numbers.append(bucket[i].pop())

def radix2(numbers , digit):
        bucket = createBucket()
        putNumberIntoBucket(numbers , digit , bucket)
        takeNumberFromBucket(numbers , bucket)


def radix_sort(numbers):
        for i in range(0 , 3):
                radix2(numbers , i)
   

def bubble_action_start(numbers , j):
        if numbers[j] > numbers[j + 1]:
                numbers[j + 1] , numbers[j] = numbers[j] , numbers[j + 1]

def do_bubble_sort_action(numbers , i):
        for j in range(0 , len(numbers) - i - 1):
                bubble_action_start(numbers , j)

def bubble_sort(numbers):
        for i in range(len(numbers)):
                do_bubble_sort_action(numbers , i)
                

def selection_action_start(numbers , j , i):
        if numbers[j] < numbers[i]:
                numbers[j] , numbers[i] = numbers[i] , numbers[j]

def do_selection_sort_action(numbers , i):
        for j in range(i + 1 , len(numbers)):
                selection_action_start(numbers , j , i)

def selection_sort(numbers):
        for i in range(len(numbers)):
                do_selection_sort_action(numbers , i)


def start_quick_sort(numbers):
        if len(numbers) <= 1:
                return numbers;
        pivot = numbers[0]
        numbers_L = []
        numbers_R = []
        for i in range(1 , len(numbers)):
                if numbers[i] <= pivot:
                        numbers_L.append(numbers[i])
                else:
                        numbers_R.append(numbers[i])
        numbers_L = start_quick_sort(numbers_L)
        numbers_R = start_quick_sort(numbers_R)
        numbers_L.append(pivot)
        return numbers_L + numbers_R

def quick_sort(numbers):
        print start_quick_sort(numbers)




def heap_insert_node(numbers , child):
        #iteratively compare to parent  , replace each other if child is smaller than parent
        parent = (child - 1) // 2
        while parent > -1 and numbers[child] < numbers[parent]:
                numbers[child] , numbers[parent] = numbers[parent] , numbers[child]
                child = parent
                parent = (child - 1) // 2
                   

def createHeapTree(numbers):
        for i in range(1 , len(numbers)):
                heap_insert_node(numbers , i)

def adjustTree(numbers , length):
        start = 0
        while start < length:
                #get childs
                L = start * 2 + 1
                R = start * 2 + 2
                #verify childs
                minIndex = start
                if L < length and numbers[L] < numbers[minIndex]:
                        minIndex = L
                if R < length and numbers[R] < numbers[minIndex]:
                        minIndex = R

                if(start == minIndex):
                        break;
                else:
                        numbers[start] , numbers[minIndex] = numbers[minIndex] , numbers[start]
                
                start = minIndex                              
                


def sortByTree(numbers):
        for i in range(len(numbers)):
                #pop minimal number from tree
                numbers[0] , numbers[len(numbers) - i - 1] = numbers[len(numbers) - i - 1] , numbers[0]
                #adjust tree
                adjustTree(numbers , len(numbers) - i - 1)

def heap_sort(numbers):
        createHeapTree(numbers)
        sortByTree(numbers)
        numbers.reverse()

if __name__ == "__main__":
        numbers = lib_number.generateNumbers(10 , 3)
        func = getattr(sys.modules[__name__] , sys.argv[1])
        print "Before:" , numbers
        func(numbers)
        print "After:" , numbers
