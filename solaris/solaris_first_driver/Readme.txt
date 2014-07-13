compile:
/opt/SUNWspro/sunstudio12.1/bin/cc -D_KERNEL -m64 -xmodel=kernel -c foobar.c

link , relocatable:
/usr/ccs/bin/ld -r -o foobar foobar.o