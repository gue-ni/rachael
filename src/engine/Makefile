CC:=g++
LFLAGS:=-O3 -Wall
CFLAGS:=-std=c++17 -g -Wall

obj:=main.o Board.o Engine.o Ply.o Square.o

.PHONY: clean all

all: engine

engine: $(obj)
	$(CC) $(LFLAGS) -o $@ $^

%.o: %.cpp
	$(CC) $(CFLAGS) $^ -c -o $@

clean:
	rm -f $(obj) engine

