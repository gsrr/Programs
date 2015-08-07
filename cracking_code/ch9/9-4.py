
# Example
'''
0 : {0}
1 : {0}, {0, 1}, {1}
2 : {0}, {0,1}, {1}, {0,2}, {0,1,2}, {1,2}
'''
#Algorithm
'''
我們可以從example看到, 假使只有一個element 0 ,
那麼他就只有一個subset {0}, 
當增加一個 element 1時, 那麼會增加兩種element:
    1. 一個是將原先所有的element增加1的新element.
    2. 一個是新element 1.
    當然還需要加上舊有的element.
'''



import copy

def combine(item , subset):
    for i in range(0, len(subset)):
        tmp = copy.copy(subset[i])
        tmp.append(item)
        subset.append(tmp)
    subset.append([item])

def subset(s):
    if len(s) == 1:
        return [s]
    slen = len(s)
    last = s.pop()
    data = subset(s)
    combine(last , data)
    return data

def main():
    print subset([0,1,2,3,4,5])


if __name__ == "__main__":
    main()
