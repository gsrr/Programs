import sys
import commands
import traceback
import copy

MSGS = "a "

def strxor(a, b):     # xor two strings of different lengths
	if len(a) > len(b):
		return "".join([chr(ord(x) ^ ord(y)) for (x, y) in zip(a[:len(b)], b)])
	else:
		return "".join([chr(ord(x) ^ ord(y)) for (x, y) in zip(a, b[:len(a)])])

def random(size=16):
	return open("/dev/urandom").read(size)

def encrypt(key, msg):
        '''
        print ord(msg[0])
        print msg.encode('hex')
        '''
        print
	c = strxor(key, msg)
	print c.encode('hex')
        return c

def main():
	key = random(1024)
        print " ".join(str(ord(x)) for x in key)
        print 
        print " ".join(str(ord(x)) for x in MSGS)
        print chr(97 ^ 79).encode('hex')
	ciphertexts = [encrypt(key, msg) for msg in MSGS]


def transToString(c_list):
    tc_list = []
    for c in c_list:
        tc_list.append("".join(chr(int(c[i : i + 2],16)) for i in range(0, len(c), 2)))

    return tc_list


def transToXor(ct, tc_list):
    stc_list = []
    for c in tc_list:
        stc_list.append(strxor(ct, c))
    return stc_list


def getXorItems(stc_list):
    space_list = []
    for c in stc_list:
        space_list.append(" " * len(c))

    return space_list

def getDecodeChr(i, de_list):
    cnt = 0
    for c in de_list:
        if len(c) > i:
            if c[i].isalpha():
                cnt += 1
    
    return cnt


def show_list(items):
    for item in items:
        print item


def combineSpacePos(space_pos_list):
    ret = {}
    for item in space_pos_list:
        for key in item.keys():
            if not ret.has_key(key):
                ret[key] = 0
            ret[key] += 1
    return ret

def getSpacePostition(stc_list):
    space_pos_list = []
    for c in stc_list:
        dec_space = " " * len(c)
        tmp = strxor(c, dec_space)
        pos_dict = {}
        for i in range(len(tmp)):
            if tmp[i].isalpha() or tmp[i] is " ":
                pos_dict[i] = tmp[i]
                
        space_pos_list.append(pos_dict)

    combineSpace = combineSpacePos(space_pos_list)
    for key in combineSpace.keys():
        if combineSpace[key] is not 11:
            del combineSpace[key]
    return combineSpace
    
        
'''
de_observe = [
        {'b' : [21], 't' : [30], 'h' : [31]}, #0
        {},#1
        {'c' : [39], 'r': [40], 'y' : [41], 'p' : [42]},#2
        {'t' : [81]},#3
        {},#4
        {'r' : [7], 'p' : [32], 'h' : [33], 'y' : [34]},#5
        {},#6
        {},#7
        {'i' : [49], 't' : [50]},#8
        {'n': [25], 'a' : [26]}, #9
        {'e' : [2, 54, 82], ' ' : [10, 35 ], 's' : [14, 36]}
    ]
'''

def getSpaceFromList(tc_list):
    space_pos = []
    for i in range(len(tc_list)):
        target = tc_list[i]
        stc_list = transToXor(target, tc_list)
        space_pos.append(getSpacePostition(stc_list))
    
    return space_pos


def find(str, ch):
    for i, ltr in enumerate(str):
        if ltr == ch:
            yield i


def getStrFromSpace(targetXor, space_pos, target_str):
    cnt = 0
    for c in targetXor:
        de_space = " " * len(c)
        tmp = strxor(de_space, c)
        for key in space_pos[cnt].keys():
            target_str[key] = tmp[key]
        cnt += 1

def getStrFromObserve(tc_list, de_observe, c_idx, target_str):
    for i in range(len(de_observe)):
        targetXor = transToXor(tc_list[i], tc_list)
        c = targetXor[c_idx]
        obs = de_observe[i]
        for key in obs.keys():
            decode = key * len(c)
            tmp = strxor(decode, c)
            for pos in obs[key]:
                target_str[pos] = tmp[pos]


def getCipherText():
    c1 = "315c4eeaa8b5f8aaf9174145bf43e1784b8fa00dc71d885a804e5ee9fa40b16349c146fb778cdf2d3aff021dfff5b403b510d0d0455468aeb98622b137dae857553ccd8883a7bc37520e06e515d22c954eba5025b8cc57ee59418ce7dc6bc41556bdb36bbca3e8774301fbcaa3b83b220809560987815f65286764703de0f3d524400a19b159610b11ef3e"
    c2 = "234c02ecbbfbafa3ed18510abd11fa724fcda2018a1a8342cf064bbde548b12b07df44ba7191d9606ef4081ffde5ad46a5069d9f7f543bedb9c861bf29c7e205132eda9382b0bc2c5c4b45f919cf3a9f1cb74151f6d551f4480c82b2cb24cc5b028aa76eb7b4ab24171ab3cdadb8356f"
    c3 = "32510ba9a7b2bba9b8005d43a304b5714cc0bb0c8a34884dd91304b8ad40b62b07df44ba6e9d8a2368e51d04e0e7b207b70b9b8261112bacb6c866a232dfe257527dc29398f5f3251a0d47e503c66e935de81230b59b7afb5f41afa8d661cb"
    c4 = "32510ba9aab2a8a4fd06414fb517b5605cc0aa0dc91a8908c2064ba8ad5ea06a029056f47a8ad3306ef5021eafe1ac01a81197847a5c68a1b78769a37bc8f4575432c198ccb4ef63590256e305cd3a9544ee4160ead45aef520489e7da7d835402bca670bda8eb775200b8dabbba246b130f040d8ec6447e2c767f3d30ed81ea2e4c1404e1315a1010e7229be6636aaa"
    c5 = "3f561ba9adb4b6ebec54424ba317b564418fac0dd35f8c08d31a1fe9e24fe56808c213f17c81d9607cee021dafe1e001b21ade877a5e68bea88d61b93ac5ee0d562e8e9582f5ef375f0a4ae20ed86e935de81230b59b73fb4302cd95d770c65b40aaa065f2a5e33a5a0bb5dcaba43722130f042f8ec85b7c2070"
    c6 = "32510bfbacfbb9befd54415da243e1695ecabd58c519cd4bd2061bbde24eb76a19d84aba34d8de287be84d07e7e9a30ee714979c7e1123a8bd9822a33ecaf512472e8e8f8db3f9635c1949e640c621854eba0d79eccf52ff111284b4cc61d11902aebc66f2b2e436434eacc0aba938220b084800c2ca4e693522643573b2c4ce35050b0cf774201f0fe52ac9f26d71b6cf61a711cc229f77ace7aa88a2f19983122b11be87a59c355d25f8e4"
    c7 = "32510bfbacfbb9befd54415da243e1695ecabd58c519cd4bd90f1fa6ea5ba47b01c909ba7696cf606ef40c04afe1ac0aa8148dd066592ded9f8774b529c7ea125d298e8883f5e9305f4b44f915cb2bd05af51373fd9b4af511039fa2d96f83414aaaf261bda2e97b170fb5cce2a53e675c154c0d9681596934777e2275b381ce2e40582afe67650b13e72287ff2270abcf73bb028932836fbdecfecee0a3b894473c1bbeb6b4913a536ce4f9b13f1efff71ea313c8661dd9a4ce"
    c8 = "315c4eeaa8b5f8bffd11155ea506b56041c6a00c8a08854dd21a4bbde54ce56801d943ba708b8a3574f40c00fff9e00fa1439fd0654327a3bfc860b92f89ee04132ecb9298f5fd2d5e4b45e40ecc3b9d59e9417df7c95bba410e9aa2ca24c5474da2f276baa3ac325918b2daada43d6712150441c2e04f6565517f317da9d3"
    c9 = "271946f9bbb2aeadec111841a81abc300ecaa01bd8069d5cc91005e9fe4aad6e04d513e96d99de2569bc5e50eeeca709b50a8a987f4264edb6896fb537d0a716132ddc938fb0f836480e06ed0fcd6e9759f40462f9cf57f4564186a2c1778f1543efa270bda5e933421cbe88a4a52222190f471e9bd15f652b653b7071aec59a2705081ffe72651d08f822c9ed6d76e48b63ab15d0208573a7eef027"
    c10 = "466d06ece998b7a2fb1d464fed2ced7641ddaa3cc31c9941cf110abbf409ed39598005b3399ccfafb61d0315fca0a314be138a9f32503bedac8067f03adbf3575c3b8edc9ba7f537530541ab0f9f3cd04ff50d66f1d559ba520e89a2cb2a83"
    c11 = "32510ba9babebbbefd001547a810e67149caee11d945cd7fc81a05e9f85aac650e9052ba6a8cd8257bf14d13e6f0a803b54fde9e77472dbff89d71b57bddef121336cb85ccb8f3315f4b52e301d16e9f52f904"

    return [c1, c2, c3, c4, c5, c6, c7, c8, c9, c10, c11]
    

def getFinalStr(target_str):
    cnt = 0
    t_ret = ""
    while target_str:
        if target_str.has_key(cnt):
            t_ret += target_str[cnt]
            del target_str[cnt]
        else:
            t_ret += "-"
        cnt += 1
    return t_ret

def getWordFormDict(word):
    re_str = "^%s$"%word
    re_str = re_str.replace("-", ".")
    output = commands.getoutput("cat /usr/share/dict/words | grep \"%s\""%(re_str)).splitlines() 
    return output

def verifyWord(word):
    output = getWordFormDict(word)
    if output and len(output) == 1:
        return True
    

def isWordExist(word):
    chk_1 = verifyWord(word)
    chk_2 = verifyWord(word.lower())
    if  not(chk_1 or chk_2):
        return False
    
    return True

def checkWord(wordBase, word_list):
    cnt = 0
    for word_dic in word_list:
        for word in word_dic.keys():
            if len(word_dic[word].intersection(wordBase)) != 0:
                cnt += 1
    return cnt

def verifyWordFromCompare(word_list):
    flag_in = True
    while flag_in:
        flag_in = False
        for word_dic in word_list:
            for word in word_dic.keys():
                validNum = checkWord(word_dic[word], word_list)
                if validNum <= 3:
                    del word_dic[word]
                    flag_in = True
    
    print

def verifyString(finalStr):
    invalidWord_list = []
    for ptxt in finalStr:
        print ptxt
        invalidWord = {}
        str_list = ptxt.split(" ")
        if len(str_list) > 1:
            for word in str_list:
                if word.count("-") == 0 and len(word) > 1:
                    if isWordExist(word) == False:
                        invalidWord[word] = set(x for x in range(ptxt.index(word), ptxt.index(word) + len(word)))
        invalidWord_list.append(invalidWord)

    verifyWordFromCompare(invalidWord_list)
    show_list(invalidWord_list)
    return invalidWord_list


def modifyString(word, i, c):
    s = list(word)
    s[i] = c
    return "".join(s)

def getProperWord(word_list):
    proper_list = []
    cnt = 0
    for word_dic in word_list:
        for word in word_dic.keys():
            print word
            for i in range(len(word)):
                re_word = modifyString(word, i, "-")
                output = getWordFormDict(re_word)
                for line in output:
                    proper_list.append((cnt, line[i], list(word_dic[word])[i], len(output)))
        cnt += 1
    proper_list = sorted(proper_list, key=lambda item:list(item)[3])
    show_list(proper_list)

def correctWrongSpell(word_list, de_observe, tc_list):
    getProperWord(word_list)


if __name__ == "__main__":
    try:
        c_list = getCipherText()
        tc_list = transToString(c_list)
        space_pos = getSpaceFromList(tc_list)
        de_observe = []
        for i in range(len(c_list)):
            de_observe.append({})
        
        oldFinalStr = []
        finalStr = []
        while len(set(finalStr).intersection(set(oldFinalStr))) != 11:
            oldFinalStr = copy.copy(finalStr)
            finalStr = [""] * 11
            for c_idx in range(len(c_list)):
                targetXor = transToXor(tc_list[c_idx], tc_list)
                target_str = {}
                getStrFromSpace(targetXor, space_pos, target_str)
                getStrFromObserve(tc_list, de_observe, c_idx, target_str) 
                finalStr[c_idx] = getFinalStr(target_str)
            
                ret_list = finalStr[c_idx].split(" ")
                ful_pos = 0
                for w in ret_list:
                    if w.count("-") < 6:
                        #print w
                        idxs = list(find(w, "-"))
                        output = getWordFormDict(w)
                        if output and len(output) == 1:
                            realWord = output[0]
                            for idx in idxs:
                                if not de_observe[c_idx].has_key(realWord[idx]):
                                    de_observe[c_idx][realWord[idx]] = []
                                de_observe[c_idx][realWord[idx]].append(ful_pos + idx + ret_list.index(w))
                    ful_pos += len(w)
                
            invalidWordList = verifyString(finalStr)
            correctWrongSpell(invalidWordList, de_observe,tc_list)

            #raw_input()
    except:
        print traceback.format_exc()

