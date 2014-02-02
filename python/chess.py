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


def getStartPoint(x , y , matrix , loc):
        _x , _y = getLoc(loc)
        chessColor = matrix[_x][_y]
        while matrix[_x][_y] == chessColor and _x + x >= 0 and _y + y >= 0:
                _x = _x + x
                _y = _y + y
        return _x , _y


def isWin(x , y , directX , directY):
        count = 1
        chessColor = matrix[x][y]
        while matrix[x + directX][y + directY] == chessColor:
                count = count + 1
                x = x + directX
                y = y + directY
                if count == 5:
                        count = 0
                        break;
        return count

def checkLU(matrix , loc):
        x , y = getStartPoint(-1 , -1 , matrix , loc)
        return isWin(x , y , 1 , 1)


def check_winner(matrix , loc):
        ret = checkLU(matrix , loc)
        if ret == 0:
                return ret
        '''
        ret = checkUD(matrix , loc)
        if ret == 0:
                return ret
        ret = checkRU(matrix , loc)
        if ret == 0:
                return ret
        ret = checkRL(matrix , loc)
        return ret
        '''

def gameStart(matrix):
        print_chessBoard(matrix)       
        while True:
                loc = raw_input("Enter your location: ")
                change_matrix(matrix , loc)
                print_chessBoard(matrix)
                ret = check_winner(matrix , loc)
                if ret == 0:
                        print "Winner , Game Over!!"
                        break
                



if __name__ == '__main__':
        matrix = [[0 for x in xrange(10)] for x in xrange(10)]
        gameStart(matrix)

