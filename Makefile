
#mish is a minimalistic shell under BSD 2 clause

CC=gcc
CFLAGS = -g 
all:
	$(CC) $(CFLAGS) main.c -o mish

clean:
	rm mish
