
import sys


class PriorityQueue:
        queue = []
        def __init__(self , data=None):
                if data:
                        self.queue.append(data)
        def display(self):
                print self.queue
        def insert(self , data):
                self.queue.append(data)
                sorted(self.queue , key=lambda x: x['age'])

if __name__ == "__main__":
        queue = PriorityQueue({'name':'A' , 'age' : 15})
        queue.display()
        queue.insert({'name':'B' , 'age' : 32})
        queue.display()

