all: bitflip

bitflip.o: bitflip.c
	cc  -c bitflip.c

clean:
	rm *.o bitflip
