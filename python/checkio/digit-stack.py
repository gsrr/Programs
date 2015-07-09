def push(s, elem):
    s.append(elem)
    return 0

def pop(s):
    if len(s) == 0:
        return 0
    
    return s.pop()

def peek(s):
    if len(s) == 0:
        return 0
    
    val = s.pop()
    s.append(val)
    return val

def digit_stack(commands):
    cmdMap = {
            "PUSH" : push,
            "POP" : pop,
            "PEEK" : peek,
    }
    s = []
    sum = 0
    for cmd in commands:
        cmdArr = cmd.split()
        func = cmdMap[cmdArr[0]]
        if len(cmdArr) == 2:
            sum = sum + func(s, int(cmdArr[1]))
        else:
            sum = sum + func(s)
    return sum

if __name__ == '__main__':
    #These "asserts" using only for self-checking and not necessary for auto-testing
    assert digit_stack(["PUSH 3", "POP", "POP", "PUSH 4", "PEEK",
                        "PUSH 9", "PUSH 0", "PEEK", "POP", "PUSH 1", "PEEK"]) == 8, "Example"
    assert digit_stack(["POP", "POP"]) == 0, "pop, pop, zero"
    assert digit_stack(["PUSH 9", "PUSH 9", "POP"]) == 9, "Push the button"
    assert digit_stack([]) == 0, "Nothing"
