
#mish is a minimalistic shell under BSD 2 clause

CC=gcc
CFLAGS = -g 
all:
	$(CC) $(CFLAGS) src/main.c -o mish

clean:
	rm mish
