

import random

def createMatrix(r,c):
    matrix = [[0 for i in xrange(c)] for i in xrange(r)]
    return matrix

def random_assign(matrix):
    for i in range(len(matrix)):
        for j in range(len(matrix[i])):
            matrix[i][j] = random.randint(0,1)

def isDie(cnt):
    if cnt < 2:
        return 0

    if cnt > 3:
        return 0

    return 1

def isAlive(cnt):
    if cnt == 3:
        return 1

    return 0

def checkSurround(i, j, matrix):
    #display_matrix(matrix)
    #raw_input()
    row = len(matrix)
    col = len(matrix[0])
    cnt = 0
    for r in [-1, 0, 1]:
        for c in [-1, 0, 1]:
            n_i = (i + r) % row
            n_j = (j + c) % col
            if n_i != i or n_j != j:
                cnt += matrix[n_i][n_j]
    
    #print "(%d,%d)"%(i,j), cnt
    if matrix[i][j] == 1:
        return isDie(cnt)
    else:
        return isAlive(cnt)

def set_cell_life(matrix):
    for i in range(len(matrix)):
        for j in range(len(matrix[i])):
            matrix[i][j] = checkSurround(i, j, matrix)
    

def display_matrix(matrix):
    for i in range(len(matrix)):
            print matrix[i]

    print 

def verifyInt(num):
    try:
        int(num)
    except:
        return -1

    return 0


def main():
    print
    r = raw_input("Please input row number:")
    c = raw_input("Please input column number:")
    
    if verifyInt(r) != 0 or verifyInt(c) != 0:
        print "[Error] : The row and column should be a number."
        return
    
    if int(r) > 100 and int(c) > 100 :
        print "[Error] : The size of matrix is too big."
        return

    matrix = createMatrix(int(r), int(c))
    random_assign(matrix)
    print "Before:"
    display_matrix(matrix)
    set_cell_life(matrix)
    print "After:"
    display_matrix(matrix)


if __name__ == "__main__":
    main()
