.SUFFIXES:
.SUFFIXES: .c .o
CLNT = llist
SRVR = llist_svc
CFLAGS = -g -Wall -lrpcsvc -lnsl

SRVR_OBJ = llist_svc_proc.o llist_xdr.o llist_svc.o
CLNT_OBJ = llist.o llist_xdr.o llist_clnt.o

.c.o:; cc -c -o $@ $(CFLAGS) $<

default: $(CLNT) $(SRVR)

$(CLNT): $(CLNT_OBJ) llist.h
	cc -o $(CLNT) $(CLNT_OBJ) -lrpcsvc -lnsl

$(SRVR): $(SRVR_OBJ) llist.h
	cc -o $(SRVR) $(SRVR_OBJ) -lrpcsvc -lnsl

clean:
	rm *.o $(CLNT) $(SRVR)
	rm -i *~
	rm core
