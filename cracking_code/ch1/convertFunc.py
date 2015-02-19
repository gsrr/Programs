import os
import glob
import sys



sourceFile = sys.argv[1]

def getLibFilePath(libFunc):
	ret =  os.walk("../lib")
	for item in ret:
		abspath = os.path.abspath(item[0])
		for file in item[2]:
			if libFunc == file.rstrip(".l"):	
				filepath = abspath + "/" + file
				return filepath

def getLibFunc(libFunc):
	ret = ""
	filepath = getLibFilePath(libFunc)
	with open(filepath, "r") as fr:
		lines = fr.readlines()
		for line in lines:
			ret = ret + line
	return ret
def main():
	with open(sourceFile, "r") as fr:
		lines = fr.readlines()
		for line in lines:
			if line.startswith("def#"):
				libFunc = line.lstrip("def#")
				print getLibFunc(libFunc.strip())
			else:
				print line.rstrip()


if __name__ == "__main__":
	main()


