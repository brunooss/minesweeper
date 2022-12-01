CC := g++
SRCDIR := src
BUILDDIR := build
TARGET := main.exe
CFLAGS := -g -Wall -O3 -std=c++11

all: main

casa:
	$(CC) $(CFLAGS) -c src/casa.cpp -o build/casa.o

vazia:
	$(CC) $(CFLAGS) -c src/vazia.cpp -o build/vazia.o

bomba:
	$(CC) $(CFLAGS) -c src/bomba.cpp -o build/bomba.o

tabuleiro:
	$(CC) $(CFLAGS) -c src/tabuleiro.cpp -o build/tabuleiro.o

main: casa vazia bomba tabuleiro
	$(CC) $(CFLAGS) build/casa.o build/vazia.o build/bomba.o build/tabuleiro.o src/main.cpp -o $(TARGET)

clean:
	$(RM) -r $(BUILDDIR)/* $(TARGET)