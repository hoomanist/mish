
#mish is a minimalistic shell under BSD 2 clause

CC=cc
CFLAGS = -g -lreadline -Wall  
all:
	mkdir built
	$(CC) $(CFLAGS) -c src/main.c -o built/main.o
	${CC} $(CFLAGS) -c src/built_in.c -o built/built_in.o
	$(CC) $(CFLAGS) built/main.o  built/built_in.o -o mish
	rm -rf built
