
#mish is a minimalistic shell under BSD 2 clause

CC=cc
CFLAGS = -g -lreadline -Wall  
all:
	$(CC) $(CFLAGS) -c src/main.c -o main.o
	${CC} $(CFLAGS) -c src/built_in.c -o built_in.o
	$(CC) $(CFLAGS) main.o  built_in.o -o mish
	rm -rf *.o
