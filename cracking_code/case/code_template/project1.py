import sys, time
import itertools
import time


def transfer(word):
    words = {
            0 : "A",
            1 : "T",
            2 : "G",
            3 : "C",
        }
    wordStr = ""
    for key in word:
        wordStr = wordStr + words[key]

    return wordStr;

def BruteForceMedianSearch(DNA, l):
    bestWord = "AAAAAAAA"
    bestDist = None
    word = [0] * 8
    diffBest = 9999
    while word:
        merf = transfer(word)
        #time.sleep(1)
        dist, diffsum = totalDistance(merf, DNA)
        print merf, diffsum, dist
        if diffsum < diffBest:
            bestWord = merf
            diffBest = diffsum
            bestDist = dist
        word = nextWord(word)
    
    print
    return bestWord, diffBest , bestDist
   
def compare(word, seq):
    pos = 0
    hd = 99
    for i in range(0,len(seq) - 8):
        tmp = 0
        for j in range(0, len(word)):
            if word[j] != seq[i + j]:
                tmp += 1
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




DNA = []
fp = open(sys.argv[1])
for line in fp:
	line = line.strip()
	DNA.append(line)

startTime = time.time()
print BruteForceMedianSearch(DNA, 8)
elapsed = time.time() - startTime
print 'It spends', elapsed, 'seconds'
