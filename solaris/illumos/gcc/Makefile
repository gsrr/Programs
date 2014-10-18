gmp:
	tar -zxvf gmp-4.3.2.tar.gz
	cd gmp-4.3.2
	./configure
	make && sudo make install
	cd ..
mpfr:
	tar -zxvf mpfr-2.4.2.tar.gz
	cd mpfr-2.4.2
	./configure
	make && sudo make install
	cd ..

gcc:
	bunzip2 il-gcc-444-i386.tar.bz2
	export GCC_ROOT=$PWD/gcc/4.4.4
	export PATH="$PWD/gcc/4.4.4/bin:$PATH"
