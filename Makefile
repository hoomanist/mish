
#mish is a minimalistic shell under BSD 2 clause

CC=gcc
CFLAGS = -g -Wall -Wextra

all:
	$(CC) $(CFLAGS) main.c -o mish

clean:
	rm mish
