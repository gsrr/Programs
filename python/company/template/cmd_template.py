import os
import sys
import cmd
import traceback
import re
sys.path.append("/var/apache/tomcat/webapps/NAS/misc/HAAgent/")
from HADefine import *
from NASHAComm import *
sys.path.append(HA_ROOT+"ExportWeb/System/")
from getSystemConfigs import *
sys.path.append(WEB_ROOT+"misc/Cmd/CmdTool/")
from cmdtool import *
from tabulate import *
from argparse import *


def createParser(func_name, usage_prefix):
	parser = ArgumentParser(
		prog=func_name,
		add_help=False,
		usage=NASCmdUsageDict.get(func_name),
		usage_prefix=usage_prefix, 
	)
	return parser

class {name}(cmd.Cmd):
	
	def __init__(self):
		cmd.Cmd.__init__(self)
		self.name = '{name}'
		self.prompt = "=>> "
		self.usage_prefix = ''
		self.cmd_loading = cmd_loading()
		self.cmd_log = cmd_log()
		self.cmd_code = cmd_code()
		self.cmd_ha_server = cmd_ha_server()
		self.cmd_query = cmd_query()
		self.initChoice()
		self.initParser()

	def initChoice(self):
		self.choice_cmd = {
			#temp:choice_cmd
			'{sub}':{},
			#fin:choice_cmd
		}
	
	def initParser(self):
		self.parser = ArgumentParser(
			prog='{name}',
			add_help=False,
			usage=NASCmdUsageDict.get('{name}'),
			usage_prefix=self.usage_prefix, 
			)
		
		#temp:create_parser
		self.parser_{sub} = createParser('{name}_{sub}', self.usage_prefix)
		#fin:create_parser
		
		#temp:add_argument
		self.parser_{sub}.add_argument(
			'{sub}',
			nargs='?',
			default=None 
		)
		#fin:add_argument
		
	@complete_twolevel
	def complete_cbackups3(self, args):
		pass
	
	#@print_cmd_manual
	def man_{name}(self, args):
		cmds=[
			#temp:man_cmd
			'{name}_{sub}',
			#fin:man_cmd
		]
		for cmd in cmds:
			print '\n'.join(['\033[1m' + NASCmdUsageDict.get(cmd),'\033[0m' + NASCmdManualDict.get(cmd)])
		self.cmd_code.print_code_msg(SYS_SUCCESSFUL)

	@print_cmd_usage
	def help_{name}(self, args):
		ret = {'status': SYS_SUCCESSFUL}
		try:
			parser_name, parser_dict = 'parser', self.choice_cmd
			if type(args) is str:
				args_list = args.split()
			else:
				args_list = list(args)
			if args_list:
				for arg in args_list[:]:
					if not arg in parser_dict.keys():
						ret = {'status': CMD_UNKNOWN}
						break
					parser_name = parser_name + '_' + arg
					parser_dict = parser_dict[arg]
				if ret.get('status') == 0:
					self.print_ntp_usage(parser_name, parser_dict)
			else:
				self.print_ntp_usage(parser_name, parser_dict)
		except:
			ret = {'status': CMD_UNKNOWN}
			self.cmd_log.cmd_except()
		finally:
			self.cmd_code.print_code_msg(ret.get('status'))
			
	@print_cmd_postcmd
	def postcmd(self, stop, line):
		"""If you want to stop the console, return something that evaluates to true.
			If you want to do some post command processing, do it here.
		"""
		return stop

	def print_{name}_usage(self, parser_name, parser_dict):
		ret = {'status': SYS_SUCCESSFUL}
		try:
			if parser_dict.keys():
				for key in parser_dict.keys():
					parser_name_key = parser_name + '_' + key
					parser_dict_key = parser_dict[key]
					self.print_ntp_usage(parser_name_key, parser_dict_key)
			else:
				getattr(self, parser_name).print_usage()
		except:
			ret = {'status': CMD_UNKNOWN}
			self.cmd_log.cmd_except()
		finally:
			return ret

	def do_{name}(self, args):
		ret = {'status': SYS_SUCCESSFUL}
		self.cmd_ha_server.start_ha_server()
		try:
			if type(args) is str:
				args_list = args.split()
			else:
				args_list = list(args)
			func_name, parser_name, parser_dict = 'cmd_{name}', 'parser', self.choice_cmd
			if args_list:
				for arg in args_list[:]:
					if not arg in parser_dict.keys():
						break
					func_name = func_name + '_' + arg
					parser_name = parser_name + '_' + arg
					parser_dict = parser_dict[arg]
					args_list.remove(arg)
				namespace = getattr(self, parser_name).parse_args(args_list).__dict__
				ret = getattr(self, func_name)(namespace)
			else:
				namespace = getattr(self, parser_name).parse_args(args_list).__dict__
				ret = getattr(self, func_name)(namespace)

		except:
			ret = {'status': CMD_UNKNOWN_PARAM} if not hasattr(sys.exc_info()[1], 'error_code') else {'status': sys.exc_info()[1].error_code}
			self.cmd_log.cmd_except()
		finally:
			self.cmd_ha_server.close_ha_server()
			return ret
	
	#temp:cmd_op
	def cmd_{name}_{sub}(self, Namespace):
		print Namespace
	#fin:cmd_op
	
