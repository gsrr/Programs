
import sys


class StartState:
	def __init__(self):
		pass
	def action(self, cxt, paras):
		line = paras['line']
		if "{name}" in line:
			cxt.s = cxt.ns
			cxt.action(paras)
		elif "#temp" in line:
			cxt.s = cxt.ts
			cxt.action(paras)
		else:
			fw = paras['fw']
			fw.write(line)
		
class nameState(StartState):
	def action(self, cxt, paras):
		fw = paras['fw']
		line = paras['line']
		name = paras['name']
		fw.write(line.replace("{name}", name))
		cxt.s = cxt.ss

class tempState(StartState):
	def action(self, cxt, paras):
		line = paras['line']
		cxt.temp.append(line)
		if "#fin" in line:
			cxt.s = cxt.wss
			cxt.action(paras)

class writeSubState(StartState):
	def action(self, cxt, paras):
		fw = paras['fw']
		name = paras['name']
		sub = paras['sub']
		
		for key in sub:
			print cxt.temp
			temp_list = list(cxt.temp[1:-1])
			print temp_list
			for line in temp_list:
				line = line.replace("{name}", name)
				line = line.replace("{sub}", key)
				fw.write(line)
		cxt.temp = []
		cxt.s = cxt.ss

class Context:
	def __init__(self):
		self.ss = StartState()
		self.ns = nameState()
		self.ts = tempState()
		self.wss = writeSubState()
		self.s = self.ss
		self.temp = []

	def action(self, paras):
		self.s.action(self, paras)

def sub(key, value, paras):
	paras[key].append(value)

def name(key, value, paras):
	paras[key] = value

def distribute(key, value, paras):
	func = getattr(sys.modules[__name__], key)(key, value, paras)

def mySplit(line):
	line = line.split("=")
	return (line[0], line[1])

def trans(tempFile, inputFile, outputFile):
	paras = {'name' : '', 'sub':[]}
	with open(inputFile, "r") as fr:
		lines = fr.readlines()
		for line in lines:
			key, value = mySplit(line.strip())			
			distribute(key, value, paras)

	with open(outputFile, "w") as fw:
		paras['fw'] = fw
		with open(tempFile, "r") as fr:
			lines = fr.readlines()
			cxt = Context()
			for line in lines:
				paras['line'] = line
				cxt.action(paras)	



if __name__ == "__main__":
	tempFile = "./cmd_template.py"
	inputFile= "./" + sys.argv[1]
	outputFile = "./" + sys.argv[1] + ".out" 
	trans(tempFile, inputFile, outputFile)
