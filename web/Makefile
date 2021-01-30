CC:=emcc

LFLAGS:=-O3 -Wall
CFLAGS:=-std=c++17 -g -Wall

obj:=main.o Board.o Engine.o Ply.o Square.o

.PHONY: clean web

all: engine web

web:
	$(CC) -std=c++17 -O3 --bind -o test.js WebEngine.cpp ../Board.cpp ../Engine.cpp ../Square.cpp ../Ply.cpp

engine: $(obj)
	$(CC) $(LFLAGS) $^ -s WASM=1 -o engine.js

%.o: ../%.cpp
	$(CC) $(CFLAGS) $^ -c -o $@

clean:
	rm -f $(obj) engine *.wasm *.js
