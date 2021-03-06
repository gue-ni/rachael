
SRC_DIR := ./src
OBJ_DIR := ./obj
#SRC_FILES := $(wildcard $(SRC_DIR)/*.cpp)
#OBJ_FILES := $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRC_FILES))

CC:=g++
FLAGS:=-O3 -Wall -Wextra -pedantic
LFLAGS:=$(FLAGS) -pthread
CFLAGS:=$(FLAGS) -std=c++11

OBJ:=obj/Board.o obj/Ply.o obj/SquareClass.o obj/Search.o obj/Evaluation.o obj/Reversible.o
RACHAEL_OBJ := obj/uci.o $(OBJ)
UNITTEST_OBJ:= obj/unittest.o $(OBJ)

.PHONY: clean all 

all: rachael unittest 

zip:
	zip -q rachael.zip Makefile src/*

rachael: $(RACHAEL_OBJ)
	$(CC) $(LFLAGS) -o $@ $^
	cp rachael lichess/lichess-bot/engines/

unittest: $(UNITTEST_OBJ)
	$(CC) $(LFLAGS) -o $@ $^

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) $^ -c -o $@

clean:
	rm -f $(OBJ_DIR)/*.o rachael unittest rachael.zip


