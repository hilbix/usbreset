CFLAGS=-Wall -O3
LDLIBS=-lusb-1.0

PROGS=reset usbreset

all:	$(PROGS)

clean:
	rm -f $(PROGS) *.o *~

