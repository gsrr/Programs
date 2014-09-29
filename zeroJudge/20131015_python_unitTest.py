import unittest

def sum(a , b):
	return a + b

class executeUnitTest(unittest.TestCase):
	def test_sum(self):
		a = 1
		b = 2
		c = sum(a , b)
		self.assertEqual(3 , c)

if __name__ == "__main__":
	unittest.main()
