
#mish is a minimalistic shell under BSD 2 clause

CC=clang
CFLAGS = -g 
all:
	$(ls -l | grep built) &> /dev/null || mkdir built
	$(CC) $(CFLAGS) -c src/main.c -o built/main.o
	$(CC) $(CFLAGS) -c src/alias.c -o built/alias.o
	$(CC) $(CFLAGS) built/main.o built/alias.o -o mish


clean:
	rm mish
	rm -rf built 
install:
	install -D mish /usr/bin

uninstall:
	rm /usr/bin/mish
