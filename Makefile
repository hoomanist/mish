
#mish is a minimalistic shell under BSD 2 clause

CC=clang
CFLAGS = -g 
all:
	mkdir built
	$(CC) $(CFLAGS) -c src/main.c -o built/main.o
	$(CC) $(CFLAGS) -c src/alias.c -o built/alias.o
	$(CC) $(CFLAGS) -c src/path.c -o built/path.o
	$(CC) $(CFLAGS) -c src/signal_handel.c -o built/signal_handel.o

	$(CC) $(CFLAGS) built/main.o built/alias.o built/path.o built/signal_handel.o -o mish
	rm -rf built

clean:
	rm mish
	rm -rf built 
install:
	install -D mish /usr/bin

uninstall:
	rm /usr/bin/mish
