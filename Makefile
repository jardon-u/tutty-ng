CC=gcc
CFLAGS=-Wall -W
SRC=buffers/buffers.c netsoul/md5_linux.c netsoul/url.c  netsoul/netsoul.c gui/tutti.c gui/dialogue.c gui/contact.c gui/fenetres.c ../c-serv/client_v1.c
debian:
	 gcc $(CFLAGS) `pkg-config --libs --cflags gtk+-2.0` $(SRC) -o tutti

openbsd:
	gcc -Wall -W `pkg-config --libs --cflags gtk+-2.0` $(SRC) -o tutti -lcrypto -lssl

exec:
	./tutti

clean:
	rm tutti


