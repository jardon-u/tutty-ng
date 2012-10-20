SRC=main.c gui/gui.c c-serv/client_v1.c buffers/buffers.c gui/tut_dialog.c gui/tut_window.c netsoul/url.c  netsoul/netsoul.c netsoul/md5_linux.c
EXEC=tutti

../$(EXEC): Makefile $(SRC)
	gcc -Wall -W `pkg-config --libs --cflags gtk+-2.0` -I. $(SRC) -o ../$(EXEC)
