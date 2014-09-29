import mmap

# write a simple example file
with open("hello.txt", "wb") as f:
	f.write("Hello Python!\n")

with open("hello.txt", "r+b") as f:
	mm = mmap.mmap(f.fileno(), 0 , access=mmap.ACCESS_WRITE)
	print mm.readline()  # prints "Hello Python!"
	print mm[:5]  # prints "Hello"
	mm[6:] = " world!\n"
	mm.seek(0)
	print mm.readline()  # prints "Hello  world!"
	print mm.size()
	mm.resize(20)
	print mm.size()
	mm[6:]="This is a test"
	mm.seek(0)
	print mm.readline()
	mm.seek(0)
	mm.write("Yaa , this is a mmap")
	mm.seek(0)
	print mm.readline()
	mm.close()

