import re

d1 = ['A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z','a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z']
d2 = ['0','1','2','3','4','5','6','7','8','9']
num_char = {1:'1', 2:'2', 3:'3', 4:'4', 5:'5', 6:'6', 7:'7', 8:'8', 9:'9', 0:'0', '0':0, '1':1, '2':2, '3':3, '4':4, '5':5, '6':6, '7':7, '8':8, '9':9}

key = 0

def set_key(k):
    global key
    key = k

def encrypt(ret):
    global key
    enc_ret = ""
    for c in ret:
        if c in d1:
            idx = d1.index(c)
            enc_ret += d1[(idx + key) % len(d1)]
        elif c in d2:
            idx = d2.index(c)
            enc_ret += d2[(idx + key) % len(d2)]
        else:
            enc_ret += c
    return enc_ret

def decrypt(ret):
    global key
    enc_ret = ""
    for c in ret:
        if c in d1:
            idx = d1.index(c)
            enc_ret += d1[(idx - key) % len(d1)]
        elif c in d2:
            idx = d2.index(c)
            enc_ret += d2[(idx - key) % len(d2)]
        else:
            enc_ret += c
    return enc_ret

def int2str(x):
    ret = ""
    while x != 0:
        val = x % 10
        ret += chr(48 + val)
        x = x // 10
    ret = ret[::-1]
    return ret

def e_repr(x):
    print x
    ret = ""
    if type(x) == str:
            ret = "\"%s\""%x
    elif type(x) == int:
        ret = int2str(x)
    elif type(x) == float:
            int_x = int(x)
            dec_x = int(100*(x - int_x))
            ret += int2str(int_x)
            ret += "."
            ret += int2str(dec_x)
            '''
            while dec_x != 0:
                dec_x = dec_x * 10
                int_x = int(dec_x)
                ret += chr(48 + int_x)
                dec_x = dec_x - int_x
            '''

    elif type(x) == list:
            ret += "["
            for item in x:
                    ret += e_repr(item)
                    ret += ","
            ret = ret.strip(",")
            ret += "]"	
    elif type(x) == dict:
            ret += "{"
            for key in x:
                    ret += e_repr(key)
                    ret += ":"
                    ret += e_repr(x[key])
                    ret += ","
            ret = ret.rstrip(",")
            ret += "}"
    elif type(x) == tuple:
            ret += "("
            for item in x:
                    ret += e_repr(item)
                    ret += ","
            ret = ret.strip(",")
            ret += ")"	
            pass	
    
    ret = encrypt(ret)
    return ret

def e_eval(x):
    print "e_eval"
    x = decrypt(x)
    ret = None
    if re.match(r'^-?[0-9]+$', x):
            ret = int(x)
    elif re.match(r'[-+]?[0-9]*\.?[0-9]+', x):
            ret = float(x)

    elif re.match(r'"(.*?)"', x):
            obj = re.match(r'"(.*?)"', x)
            ret = obj.group(1)
    elif re.match(r'{(.*?)}', x):
            obj = re.match(r'{(.*?)}', x)
            ret = {}
            cont = obj.group(1)
            cont_arr = cont.split(",")
            for item in cont_arr:
                    item_arr = item.split(":")
                    ret[e_eval(item_arr[0])] = e_eval(item_arr[1])
    elif re.match(r'\((.*?)\)', x):
            obj = re.match(r'\((.*?)\)', x)
            ret = []
            cont = obj.group(1)
            cont_arr = cont.split(",")
            for item in cont_arr:
                    ret.append(e_eval(item))
            
            ret = tuple(ret)
    elif re.match(r'\[(.*?)\]', x):
            obj = re.match(r'\[(.*?)\]', x)
            ret = []
            cont = obj.group(1)
            cont_arr = cont.split(",")
            for item in cont_arr:
                    ret.append(e_eval(item))
            
    print type(ret)
    return ret

def main():
    set_key(1)
    print e_eval("11")
    print e_eval("\"22\"")

    print "test float"
    f_str = e_repr(123.12)
    print e_eval(f_str)

    print "test dict"
    dict_str = e_repr({"a":11, "b":22, "22":33})
    print dict_str
    print e_eval(dict_str)

    print "test tuple"
    tuple_str = e_repr((11, 22, "33"))
    print tuple_str
    print e_eval(tuple_str)

    print "test list"
    list_str = e_repr(["11", 22, "33"])
    print list_str
    print e_eval(list_str)

if __name__ == "__main__":
	main()
