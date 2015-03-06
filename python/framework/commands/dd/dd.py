import os

def hello():
    print "hello world!"

def create_file(paras):
    print paras
    outPath = paras[0]
    size = paras[1]

    cmd = "dd if=/dev/urandom of=%s bs=1048576 count=%s"%(outPath, size)
    os.system(cmd)
