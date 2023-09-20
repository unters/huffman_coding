# Not ready!
# add ./out folder to store .o files
# CFLAGS?

CC = gcc
CFLAGS = -c

all: huffman_encoding

debug: main.o huffman.o
	$(CC) main.o huffman.o -g -o main

huffman_encoding: main.o huffman.o huffman_structures.o
	$(CC) main.o huffman.o -o main

main.o: main.c
	$(CC) $(CFLAGS) src/main.c

huffman.o: huffman.c
	$(CC) $(CFLAGS) src/huffman.c

huffman_structures.o: huffman_structures.c
	$(CC) $(CFLAGS) src/huffman_structures.c

clean:
	rm -rf *.o
