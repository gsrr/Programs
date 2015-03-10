import sys
import os



def showProbeReturn(paras):
	name = paras[0]
	probe = paras[1]
	valType = paras[2]
	if valType == "string":
		fmt = "\"%s\\n\",copyinstr(arg1)"
	else:
		fmt = "\"%d\n\", arg1"
	cmd = "dtrace -n 'pid$target::%s {printf(%s)}' -c %s"%(probe, fmt, name)
	os.system(cmd)

# dtrace -ln 'pid$target:::return' -p pid
def listProbesByPid(paras):
	pass

# dtrace -ln 'pid$target:::return' -c hellO
def listProbesByProgram(paras):
	name = paras[0]
	cmd = "dtrace -ln 'pid$target:::entry' -c %s"%(name)
	os.system(cmd)
	cmd = "dtrace -ln 'pid$target:::return' -c %s"%(name)
	os.system(cmd)

def main():
	if len(sys.argv) < 2:
		return
	
	func = getattr(sys.modules[__name__], sys.argv[1])
	func(sys.argv[2:])
	

if __name__ == "__main__":
	main()
