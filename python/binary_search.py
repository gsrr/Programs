import lib_number
import sys

class Node:
        numbers = []
        def __init__(self , data):
                self.left = None
                self.right = None
                self.data = data
        def insert(self , data):
                if data < self.data:
                        if self.left == None:
                                self.left = Node(data)
                        else:
                                self.left.insert(data)
                else:
                        if self.right == None:
                                self.right = Node(data)
                        else:
                                self.right.insert(data)
        
        def DLR(self):
                self.numbers.append(self.data)
                if self.left != None:
                        self.left.DLR()
                if self.right != None:
                        self.right.DLR()
                return self.numbers
                        
        
        def LDR(self):
                if self.left != None:
                        self.left.LDR()

                self.numbers.append(self.data)

                if self.right != None:
                        self.right.LDR()
                return self.numbers
        
        def LRD(self):
                if self.left != None:
                        self.left.LRD()

                if self.right != None:
                        self.right.LRD()

                self.numbers.append(self.data)

                return self.numbers
        
        
        def display(self , style):
                func = getattr(self , style) 
                return func()



def createBinaryTree(numbers):
        root = Node(numbers[0])
        for i in range(1 , len(numbers)):
                root.insert(numbers[i])

        return root.display("LDR")

if __name__ == "__main__":
        numbers = lib_number.generateNumbers(10, 2)
        print numbers
        print createBinaryTree(numbers)
