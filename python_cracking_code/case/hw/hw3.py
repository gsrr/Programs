import re


def e_repr(x):
	ret = ""
	if type(x) == str:
		ret = "\"%s\""%x
	elif type(x) == int:
		while x != 0:
			val = x % 10
			ret += chr(48 + val)
			x = x / 10
			ret = ret[::-1]
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
		pass	

	return ret

def e_eval(x):
	ret = None
	if re.match(r'\d+', x):
		ret = int(x)
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
	print type(ret)
	return ret

def main():
	print e_repr({"a":11, "b":22, "22":33})
	print e_repr(["11", 22, "33"])
	print e_eval("11")
	print e_eval("\"22\"")
	dict_str = e_repr({"a":11, "b":22, "22":33})
	print e_eval(dict_str)

if __name__ == "__main__":
	main()
