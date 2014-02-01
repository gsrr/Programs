import os

def print_chessBoard(matrix):
        os.system('clear')
        for elem in matrix:
                print elem , '\n' 

def getLoc(loc):
        x = int(loc.split(",")[0])
        y = int(loc.split(",")[1])
        return (x , y)

def change_matrix(matrix , loc):
        x , y = getLoc(loc)
        matrix[x][y] = 1

def gameStart(matrix):
        print_chessBoard(matrix)       
        while True:
                loc = raw_input("Enter your location: ")
                change_matrix(matrix , loc)
                print_chessBoard(matrix)
                



if __name__ == '__main__':
        matrix = [[0 for x in xrange(10)] for x in xrange(10)]
        gameStart(matrix)

