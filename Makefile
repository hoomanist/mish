
#mish is a minimalistic shell under BSD 2 clause

CC=cc
CFLAGS = -g -lreadline -Wall  
all:
	if [ ! -d "./build/" ];	then mkdir build; fi
	$(CC) $(CFLAGS) -c src/main.c -o build/main.o
	${CC} $(CFLAGS) -c src/built_in.c -o build/built_in.o
	$(CC) $(CFLAGS) build/main.o  build/built_in.o -o mish
	rm -rf *.o

clean:
	rm build/built_in.o build/main.o
	rmdir build