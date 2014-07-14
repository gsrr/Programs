import smtplib
import unittest

class TestSMTP(unittest.TestCase):
	user = ""
	passwd = ""

	def test_normal(self):
		server = smtplib.SMTP('192.168.99.53', 25)
		server.sendmail('nas@infortrend.com', 'jerry.cheng@infortrend.com', '\ntest')
		server.quit()
	
	def test_tls(self):
		server = smtplib.SMTP('smtp.gmail.com', 587)
		server.starttls()
		server.login(self.user, self.passwd)
		server.sendmail('nas@gmail.com', 'jerry.cheng@infortrend.com', '\ntest_tls')
		server.quit()
	def test_ssl(self):
		server = smtplib.SMTP_SSL('74.125.129.108', 465)
		server.login(self.user, self.passwd)
		server.sendmail('nas@gmail.com', 'jerry.cheng@infortrend.com', '\ntest_ssl')
		server.quit()
	

if __name__ == "__main__":
	import sys
	TestSMTP.passwd = sys.argv.pop()
	TestSMTP.user = sys.argv.pop()
	
	unittest.main()
	
