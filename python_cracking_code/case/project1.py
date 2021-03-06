import sys, time
import itertools
import time

DEBUG = False

def myprint(msg):
    if DEBUG:
        print msg 
        time.sleep(1)

def transfer(word):
    words = {
            0 : "A",
            1 : "T",
            2 : "G",
            3 : "C",
        }
    wordStr = [" "] * 8
    for i in range(0, len(word)):
        wordStr[i] = words[word[i]]

    return "".join(wordStr)

def nextWord(word):
    carry = 1
    i = 0
    while i < 8:
        tmp = word[i] + carry
        word[i] = tmp % 4
        carry = tmp / 4
        if carry == 0:
            break
        i += 1

    if i == 8:
        return None
    else:
        return word
   
def compare(word, seq):
    myprint(seq)
    pos = 0
    hd = 99
    for i in range(0,len(seq) - 7):
        tmp = 0
        for j in range(0, len(word)):
            if word[j] != seq[i + j]:
                tmp += 1
        myprint(word[0 : 8] + ":" + seq[i : i + 8] + ":" + str(tmp))
        if tmp < hd:
            hd = tmp
            pos = i
    
    return pos , hd

def totalDistance(word, DNA):
    dist = []
    diffsum = 0
    for seq in DNA:
        pos, score = compare(word, seq)
        dist.append(pos)
        diffsum += score

    return dist, diffsum 

def BruteForceMedianSearch(DNA, l):
    bestWord = "AAAAAAAA"
    bestDist = None
    word = [0] * 8
    diffBest = 9999
    while word:
        merf = transfer(word)
        dist, diffsum = totalDistance(merf, DNA)
        print merf, diffsum, dist
        if diffsum < diffBest:
            bestWord = merf
            diffBest = diffsum
            bestDist = dist
        word = nextWord(word)
    
    print
    return bestWord, diffBest , bestDist

def readData():
    DNA = []
    fp = open(sys.argv[1])
    for line in fp:
            line = line.strip()
            DNA.append(line)

    return DNA

def main():
    if len(sys.argv) > 2:
        if sys.argv[2] == "debug":
            DEBUG = True

    DNA = readData()
    startTime = time.time()
    print BruteForceMedianSearch(DNA, 8)
    elapsed = time.time() - startTime
    print 'It spends', elapsed, 'seconds'
    

if __name__ == "__main__":
    main()

