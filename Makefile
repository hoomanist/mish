
#mish is a minimalistic shell under BSD 2 clause

CC=clang
CFLAGS = -g 
all:
	$(CC) $(CFLAGS) -c src/main.c 
	$(CC) $(CFLAGS) -c src/alias.c
	$(CC) $(CFLAGS) main.o alias.o -o mish


clean:
	rm mish
	rm *.o
install:
	install -D mish /usr/bin

uninstall:
	rm /usr/bin/mish
