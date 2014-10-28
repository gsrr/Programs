CC       = gcc
CPPFLAGS = 
CFLAGS   = -Os -Wall
LDFLAGS	 =
CONFIGURE_ARGS =

all: dhcpdiscover

dhcpdiscover: 
	$(CC) -o dhcpdiscover dhcpdiscover.c
	$(CC) -o dhcpdiscover_attack dhcpdiscover_attack.c

clean:
	rm -f dhcpdiscover
	rm -f dhcpdiscover_atack
