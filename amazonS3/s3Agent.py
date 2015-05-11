import os
import sys
import subprocess
import commands
import time

def isZombie(pid):
	output = commands.getoutput("ps -ef | grep %d"%pid).splitlines()
	for line in output:
		if "<defunct>" in line:
			return True


def checkPid(pid):
	try:
		os.kill(pid, 0)
	except OSError:
		return False
	
	if isZombie(pid):
		return False

	return True


def errorHandle(key):
	errorMsg = {
		'source folder not exist' : 'ERROR: Parameter problem: Destination must be a directory when downloading multiple sources.',
		'can not access target folder' : 'ERROR: S3 error: Access Denied',
		'bucket not exist' : 'ERROR: S3 error: 404 (NoSuchBucket): The specified bucket does not exist'
	}

class Base(object):
	def __init__(self, cfg):
		self.cfg = cfg
		self.option = ['-qr', '--no-mime-magic', '--no-progress'] 
		self.advOpt_on = {
			'Reduce_Redund': '--reduced-redundancy',
			'Server_Enc': '--server-side-encryption',
			'Delete_Extra_File': '--delete-removed'
		}
		self.advOpt_off = {
			'Incremental_Rep': '-f'
		}
	
	def adv_option(self):
		advOpt = []
		for key in self.advOpt_on.keys():
			if self.cfg[key] == 'on':
				advOpt.append(self.advOpt_on[key])

		return advOpt
	
	def options(self):
		self.option = self.option + self.adv_option()
		self.option = self.option + self.cmd_option()
		return self.option
		
class Download(Base):
	def __init__(self, cfg):
		Base.__init__(self, cfg)

	def cmd_option(self):
		if self.cfg['Incremental_Rep'] == 'off':
			return ['-f', 'get']
		return ["sync"]	

	def paras(self):
		cfg = self.cfg
		return [cfg['tgt_folder'], cfg['src_folder']]
	
class Upload(Base):
	def __init__(self, cfg):
		Base.__init__(self, cfg)

	def cmd_option(self):
		if self.cfg['Incremental_Rep'] == 'off':
			return ['-f', 'put']
		return ["sync"]	

	def paras(self):
		cfg = self.cfg
		return [cfg['src_folder'], cfg['tgt_folder']]
		
class DryRun(Base):
	def __init__(self, cfg):
		Base.__init__(self, cfg)

	def cmd_option(self):
		return ["sync"]

	def options(self):
		self.option.append('-n')	
		super(DryRun, self).options()
		return self.option
	
	def paras(self):
		cfg = self.cfg
		return [cfg['src_folder'], cfg['tgt_folder']]
	

class s3Cmd:
	def __init__(self, cfg, op):
		self.obj = {
			'download': Download(cfg),
			'upload' : Upload(cfg),
			'dryRun' : DryRun(cfg)
		}[op]
		self.cfg = cfg
		self.op = op

	def s3Options(self):
		option = self.obj.options()	
		return " ".join(option)

	def cmdList(self):
		cfg = self.cfg
		option = (cfg['access_key'], cfg['secret_key'], self.s3Options())
		cmd = '/usr/bin/s3cmd --access_key=%s --secret_key=%s %s'%option
		self.cmdList = cmd.split(" ") + self.obj.paras()
		
		return self.cmdList
		
	def cmdStr(self):
		return " ".join(self.cmdList)

def errorMsg(errCode):
	try:
		errMsg = {
			501 : "Please check the setting of dns server!",
			502 : "The AWS Access Key Id you provided does not exist.",
			503 : "The request signature we calculated does not match the signature you provided.",
			504 : "The specified bucket does not exist.",
		}[errCode]

		print errMsg
	except:
		pass


def execute(cmd):
	ret = {'status' : 0}
	cmdList = cmd.cmdList()
	print cmd.cmdStr()
        try:
            p = subprocess.Popen(cmdList,  stderr=subprocess.PIPE)
            while checkPid(p.pid):
                    line = p.stderr.readline().strip()
                    print line
                    if "node name or service name not known" in line:
                            ret['status'] = 501
                            break
                    elif "The AWS Access Key Id you provided does not exist" in line:
                            ret['status'] = 502
                            break
                    elif "The request signature we calculated does not match the signature you provided" in line:
                            ret['status'] = 503
                            break
                    elif "The specified bucket does not exist" in line:
                            ret['status'] = 504
                            break
            
            errorMsg(ret['status'])
            return ret
        except:
            print "Warning:Please Install the s3Cmd first"

def restore_download(cfg):
	cmd = s3Cmd(cfg, 'upload')
	execute(cmd)
	
def restore_upload(cfg):
	cmd = s3Cmd(cfg, 'download')
	execute(cmd)

def start_download(cfg):
	cmd = s3Cmd(cfg, 'download')
	execute(cmd)
	
def start_upload(cfg):
	cmd = s3Cmd(cfg, 'upload')
	execute(cmd)

def dryRun_upload(cfg):
	cmd = s3Cmd(cfg, 'dryRun')
	print "dryRunTest=" + str(execute(cmd))

def dryRun_download(cfg):
	print dryRun_upload(cfg)

def loadConfig(cfgPath):
	cfg = {}
	with open(cfgPath, 'r') as fr:
		lines = fr.readlines()
		for line in lines:
			key, value = line.split("=")
			cfg[key] = value.strip()
	
	return cfg

def testtimeout_upload(cfg):
	time.sleep(600)
	cmd = s3Cmd(cfg, 'upload')
	execute(cmd)
	
def main():
        if len(sys.argv) < 3:
            print "python s3Agent.py start/restore s3.config"
            return
	op = sys.argv[1]
	cfgFile = sys.argv[2]
	cfg = loadConfig(cfgFile)
	func = getattr(sys.modules[__name__], str(op + "_" + cfg['backup_type'].strip()))
	func(cfg)


if __name__ == "__main__":
	main()
