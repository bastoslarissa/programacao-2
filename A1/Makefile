CC = gcc
CFLAGS = -Wall -g

all: gbv

gbv: mainteste.o gbv.o util.o
	$(CC) $(CFLAGS) -o gbv mainteste.o gbv.o util.o

mainteste.o: mainteste.c gbv.h
	$(CC) $(CFLAGS) -c mainteste.c

gbv.o: gbv.c gbv.h
	$(CC) $(CFLAGS) -c gbv.c

util.o: util.c util.h
	$(CC) $(CFLAGS) -c util.c

clean:
	rm -f *.o gbv

