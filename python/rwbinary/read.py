import binascii
import struct

with open("/root/test_hello.pyc", "wb") as fw:
	with open("/root/test.pyc", "rb") as fr:
		data = fr.read(1)
		cnt = 1
		while data:
			print cnt, ":", data.encode("hex")
			if cnt == 50:
				fw.write(struct.pack("B", 73))
			else:
				fw.write(data)
			data = fr.read(1)
			cnt += 1

